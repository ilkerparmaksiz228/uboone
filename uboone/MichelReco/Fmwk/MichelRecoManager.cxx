#ifndef MICHELRECOMANAGER_CXX
#define MICHELRECOMANAGER_CXX

#include "MichelRecoManager.h"
#include "MichelException.h"
#include <sstream>
#include <iomanip>

namespace michel {

  //-----------------------------------------------------------------
  MichelRecoManager::MichelRecoManager()
    //-----------------------------------------------------------------
    : _d_cutoff           ( 6.0 ) //Used to be 3.6
    , _min_nhits          ( 4   ) //Used to be 25
    , _alg_merge          ( nullptr )
    , _alg_filter         ( nullptr )
    , _alg_v              ( )
  {
    _event_time = 0;
    _event_ctr  = 0;
  }

  //---------------------------------------------------------
  bool MichelRecoManager::Append(std::vector<michel::HitPt>&& hit_v,const size_t& idx)
  //---------------------------------------------------------
  {
    if (hit_v.size() < _min_nhits) return false;
    MichelCluster cluster(std::move(hit_v), _min_nhits, _d_cutoff);
    cluster.setInputCluster(std::make_pair((unsigned short)idx,cluster._hits.size()));
    // if the cluster has no hits -> do not append
    if (cluster._hits.size() == 0)
      return false;
    cluster.SetVerbosity(_verbosity);
    if (cluster._hits.size() < _min_nhits) return false;
    _input_v.emplace_back(cluster);
    _input_v.back()._id = (_input_v.size() - 1);

    if (_verbosity <= msg::kINFO) {
      std::stringstream ss;
      ss << "Added input cluster with ID " << _input_v.back()._id;
      Print(msg::kINFO, __FUNCTION__, ss.str());
    }
    
    return true;
  }
  
  //---------------------------------------------------------------------------
  void MichelRecoManager::RegisterAllHits(const std::vector<michel::HitPt>& all_hit_v)
  //---------------------------------------------------------------------------
  {
    if (all_hit_v.empty()) {
      std::cerr << "\033[93m[ERROR]\033[00m cannot have hit & marker list w/ different length..."
		<< std::endl;
      throw MichelException();
    }
    _all_hit_v = all_hit_v;
  }
  
  //-----------------------------------------------------------------
  void MichelRecoManager::RegisterAllHits(std::vector<michel::HitPt>&& all_hit_v)
  //-----------------------------------------------------------------
  {
    if (all_hit_v.empty()) {
      std::cerr << "\033[93m[ERROR]\033[00m cannot have hit & marker list w/ different length..."
		<< std::endl;
      throw MichelException();
    }
    std::swap(_all_hit_v, all_hit_v);
  }
  
  //-----------------------------------------------------------------
  void MichelRecoManager::AddMergingAlgo(BaseAlgMerger* algo)
  //-----------------------------------------------------------------
  {
    _alg_merge = algo;
    _merge_time = 0;
    _merge_ctr  = 0;
  }

  //-----------------------------------------------------------------
  void MichelRecoManager::AddFilteringAlgo(BaseAlgFilter* algo)
  //-----------------------------------------------------------------
  {
    _alg_filter = algo;
  }
  
  //-----------------------------------------------------------------
  void MichelRecoManager::AddAlgo(BaseMichelAlgo* algo)
  //-----------------------------------------------------------------
  {
    _alg_v.push_back(algo);
    _alg_time_v.push_back(0.);
    _alg_ctr_v.push_back(0);
  }
  
  //-----------------------------------------------------------------
  void MichelRecoManager::AddAna(MichelAnaBase* ana)
  //-----------------------------------------------------------------
  {
    _ana_v.push_back(ana);
  }
  
  //-----------------------------------------------------------------
  void MichelRecoManager::Initialize()
  //-----------------------------------------------------------------
  {
    for (auto& ana : _ana_v) {
      ana->SetVerbosity(_verbosity);
      ana->Initialize();
    }
  }
  
  void MichelRecoManager::Process() {

    _event_watch.Start();
    
    if (_verbosity <= msg::kDEBUG)
      Print(msg::kDEBUG, __FUNCTION__, "start!");
    
    // If nothing to be done, return
    if (_input_v.empty()) return;

    /*
    // make sure hit vectors provided & cluster list (another hit arrays) are consistent
    _used_hit_marker_v.resize(_all_hit_v.size(), false);
    for (size_t i = 0; i < _used_hit_marker_v.size(); ++i) {
      if (_all_hit_v[i]._pl != 2) //check plane
	_used_hit_marker_v[i] = true;
      else
	_used_hit_marker_v[i] = false;
    }
    */
    
    if (_verbosity <= msg::kDEBUG) {
      
      std::stringstream ss;
      ss << "running algo : " << _alg_merge->Name();
      Print(msg::kDEBUG, __FUNCTION__, ss.str());
      
    }

    // Step 0 ...Filter clusters
    if (_alg_filter){
      MichelClusterArray filtered_clusters;
      for (auto const& cluster : _input_v)
	if (_alg_filter->FilterCluster(cluster) == true) { filtered_clusters.push_back(cluster); }
      _input_v = filtered_clusters;
    }
    
    //
    // Step 1 ... merge clusters
    //
    if (!_alg_merge)
      _output_v = _input_v;
    
    else {
      _watch.Start();
      _output_v = _alg_merge->Merge(_input_v);
      _merge_time += _watch.RealTime();
      _merge_ctr  += _input_v.size();

    }

    // save merged clusters
    _merged_v = _output_v;

    std::vector<MichelCluster> processed_cluster_v;
    processed_cluster_v.reserve(_output_v.size());

    // loop through the various clusters
    for (auto& cluster : _output_v ) {
      // start going through algorithms and executing
      // them consecutively
      bool keep = true;
      for (size_t n = 0; n < _alg_v.size() && keep; n++) {
	if (_verbosity <= msg::kINFO) {
	  std::stringstream ss;
	  ss << "running algo : " << _alg_v[n]->Name()
	     << "(" << n << ")"
	     << " on MichelCluster ID: " << cluster._id;
	  Print(msg::kINFO, __FUNCTION__, ss.str());
	}
	_watch.Start();
	MichelCluster before(cluster);
	keep = _alg_v[n]->ProcessCluster(cluster, _all_hit_v);
	auto const diff_msg = before.Diff(cluster);
	if ( !diff_msg.empty() && ( _verbosity <= msg::kDEBUG ) ) {
	  std::stringstream ss;
	  ss << "\033[93m Detected a change in MichelCluster (ID=" << cluster._id << ")!\033[00m"
	     << " by algorithm "
	     << "\033[95m " << _alg_v[n]->Name() << " (" << n << ") \033[00m" << std::endl
	     << diff_msg;
	  Print(msg::kDEBUG, __FUNCTION__, ss.str());
	}
	_alg_time_v[n] += _watch.RealTime();
	_alg_ctr_v[n] += 1;
	if (!keep && _verbosity <= msg::kINFO) {
	  std::stringstream ss;
	  ss << "dropping MichelCluster due to algorithm: "
	     << _alg_v[n]->Name();
	  Print(msg::kINFO, __FUNCTION__, ss.str());
	}
      }// looping through algorithms
      
      // If keep is true, move it
      if (keep) {
	if (_verbosity <= msg::kINFO) {
	  std::stringstream ss;
	  ss << " Saving cluster with ID " << cluster._id;
	  Print(msg::kINFO, __FUNCTION__, ss.str());
	}
	processed_cluster_v.push_back(MichelCluster());
	std::swap(cluster, processed_cluster_v.back());
      }
    }// for all clusters
    std::swap(processed_cluster_v, _output_v);
    
    //
    // Finally call analyze
    //
    if (_output_v.size() > 0){
      for (auto& ana : _ana_v) {
	// firs set the event id for the ana
	ana->SetEventID(_id);
	ana->Analyze(_input_v, _output_v);
      }
    }// if there are any outputs to begin with
    
    if (_verbosity <= msg::kINFO)
      Print(msg::kINFO, __FUNCTION__, " Done!");


    _event_time += _event_watch.RealTime();    
    _event_ctr  += 1;

    return;
  }// end Process function
  
  //-----------------------------------------------------------------
  void MichelRecoManager::EventReset()
  //-----------------------------------------------------------------
  {
    for (auto& alg : _alg_v) if (alg) alg->EventReset();
    for (auto& ana : _ana_v) ana->EventReset();
    _input_v.clear();
    _output_v.clear();
  }
  
  //-----------------------------------------------------------------
  void MichelRecoManager::Finalize()//TFile *fout)
  //-----------------------------------------------------------------
  {
    
    //for (auto& ana : _ana_v) ana->Finalize(fout);
    
    // loop through algos and evaluate time-performance
    std::cout << std::endl
	      << "========================================= Time Report =========================================" << std::endl;
    if (_alg_merge){
      double merge_time = _merge_time / _merge_ctr;
      std::cout <<  std::setw(25) << _alg_merge->Name() << "\t Merge Time: " 
		<< std::setw(10) << merge_time * 1.e6  << " [us/cluster]"
		<< "\t Clusters Scanned: " << _merge_ctr << std::endl
		<< "===============================================================================================" << std::endl;
    }
    for (size_t n = 0; n < _alg_v.size(); n++) {
      double alg_time = _alg_time_v[n] / ((double)_alg_ctr_v[n]);
      std::cout <<  std::setw(25) << _alg_v[n]->Name() << "\t Algo Time: " 
		<< std::setw(10) << alg_time * 1.e6  << " [us/cluster]"
		<< "\t Clusters Scanned: " << _alg_ctr_v[n] << std::endl;
      if (_alg_v[n]->Name() == "CalcTruncated")
	_alg_v[n]->EventReset();
      _alg_v[n]->Report();
      std::cout << "===============================================================================================" << std::endl;
    }// for all algorithms
    double event_time = _event_time/_event_ctr;
    std::cout <<  std::setw(37) << "\t Full Event Time: " 
	      << std::setw(12) << event_time * 1.e6  << " [us/event]"
	      << "\t Events Scanned: " << _event_ctr << std::endl;
    std::cout << "===============================================================================================" << std::endl;
    
  }
}
#endif
  
