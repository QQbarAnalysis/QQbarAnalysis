#ifndef _SummaryData_hh
#define _SummaryData_hh
namespace QQbarProcessor 
{

  struct StatsData_QQbar  {
  public:

    float _mc_quark_E[2];
    float _mc_quark_px[2];
    float _mc_quark_py[2];
    float _mc_quark_pz[2];
    float _mc_quark_m[2];
    float _mc_quark_pdg[2];
    float _mc_quark_charge[2];

    float _mc_ISR_E[2]; 
    float _mc_ISR_px[2];
    float _mc_ISR_py[2]; 
    float _mc_ISR_pz[2]; 
    float _mc_ISR_m[2];  
    float _mc_ISR_pdg[2];
    float _mc_ISR_charge[2]; 

    float _mc_quark_ps_E[1000];
    float _mc_quark_ps_px[1000];
    float _mc_quark_ps_py[1000];
    float _mc_quark_ps_pz[1000];
    float _mc_quark_ps_m[1000];
    float _mc_quark_ps_pdg[1000];
    float _mc_quark_ps_charge[1000];
    int  _mc_quark_ps_n;
    float _mc_quark_ps_y12;
    float _mc_quark_ps_y23;
    float _mc_quark_ps_d12;
    float _mc_quark_ps_d23;
    float _mc_quark_ps_jet_E[2];
    float _mc_quark_ps_jet_px[2];
    float _mc_quark_ps_jet_py[2];
    float _mc_quark_ps_jet_pz[2];

    //Member for Stable (Added by Seidai in 2020.Sep.17)
    float _mc_stable_E[1000];
    float _mc_stable_px[1000];
    float _mc_stable_py[1000];
    float _mc_stable_pz[1000];
    float _mc_stable_m[1000];
    int _mc_stable_pdg[1000];
    float _mc_stable_charge[1000];
    int _mc_stable_isoverlay[1000];
    int _mc_stable_isisr[1000];
    int _mc_stable_n;
    float _mc_stable_y12;
    float _mc_stable_y23;
    float _mc_stable_d12;
    float _mc_stable_d23;
    float _mc_stable_jet_E[2];
    float _mc_stable_jet_px[2];
    float _mc_stable_jet_py[2];
    float _mc_stable_jet_pz[2];

    //jet stuff
    float _y23;
    float _y12;
    float _d23;
    float _d12;
    float _oblateness;
    float _aplanarity;
    float _major_thrust_value;
    float _minor_thrust_value;
    float _principle_thrust_value;
    float _sphericity;
    float _major_thrust_axis[3];
    float _minor_thrust_axis[3];
    float _principle_thrust_axis[3];
    float _sphericity_tensor[3];

    float _jet_E[2];
    float _jet_px[2];
    float _jet_py[2];
    float _jet_pz[2];
    float _jet_btag[2];
    float _jet_ctag[2];

    //pfo stuff
    int _pfo_jet_match[1000];
    float _pfo_E[1000];
    float _pfo_px[1000];
    float _pfo_py[1000];
    float _pfo_pz[1000];
    float _pfo_m[1000];
    int _pfo_type[1000]; 
    int _pfo_charge[1000];
    int _pfo_ntracks[1000];
    int _pfo_pdgcheat[1000];
    int _pfo_isoverlay[1000];
    int _pfo_isisr[1000];
    int _pfo_istrack[1000];
    int _pfo_vtx[1000];

    int _pfo_tpc_hits[1000];
    float _pfo_dedx[1000];
    float _pfo_dedxerror[1000];
    float _pfo_d0[1000];
    float _pfo_d0error[1000];
    float _pfo_z0[1000];
    float _pfo_z0error[1000];
    float _pfo_phi[1000];
    float _pfo_phierror[1000];
    float _pfo_omega[1000];
    float _pfo_omegaerror[1000];
    float _pfo_tanlambda[1000];
    float _pfo_tanlambdaerror[1000];
    float _pfo_chi2[1000];
    float _pfo_ndf[1000];
    int _pfo_pid[1000];
    float _pfo_pid_likelihood[1000];
    int _pfo_piddedx[1000];
    float _pfo_piddedx_likelihood[1000];

    int _pfo_n;
    int _nvtx;

    int _pfo_n_j1;
    int _pfo_n_j2;
    int _nvtx_j1;
    int _nvtx_j2;


    void Clear()  {

      for (unsigned int i = 0; i < 1000; i++) {
	_mc_quark_ps_E[i]=0;
	_mc_quark_ps_px[i]=0;
	_mc_quark_ps_py[i]=0;
	_mc_quark_ps_pz[i]=0;
        _mc_quark_ps_m[i]=0;
	_mc_quark_ps_pdg[i]=-1000;
	_mc_quark_ps_charge[i]=-1000;
      }

      _mc_quark_ps_n=0;
      _mc_quark_ps_y12=0;
      _mc_quark_ps_y23=0;
      _mc_quark_ps_d12=0;
      _mc_quark_ps_d23=0;

      for (unsigned int i = 0; i < 2; i++) {
	_mc_quark_E[i]=0;
	_mc_quark_px[i]=0;
	_mc_quark_py[i]=0;
	_mc_quark_pz[i]=0;
	_mc_quark_m[i]=0;
	_mc_quark_pdg[i]=-1000;
	_mc_quark_charge[i]=-1000;

	_mc_ISR_E[i]=0;
        _mc_ISR_px[i]=0;
        _mc_ISR_py[i]=0;
        _mc_ISR_pz[i]=0;
        _mc_ISR_m[i]=0; 
        _mc_ISR_pdg[i]=-1000;
        _mc_ISR_charge[i]=-1000;

	_mc_quark_ps_jet_E[i]=0;
	_mc_quark_ps_jet_px[i]=0; 
	_mc_quark_ps_jet_py[i]=0; 
	_mc_quark_ps_jet_pz[i]=0; 
      }
      
      //Added by Seidai 2020.Sep.21
      for(int i=0; i<1000; i++) {
        _mc_stable_E[i]=0;
        _mc_stable_pdg[i]=0;
        _mc_stable_px[i]=0;
        _mc_stable_py[i]=0;
        _mc_stable_pz[i]=0;
        _mc_stable_m[i]=0;
        _mc_stable_charge[i]=0;
        _mc_stable_isisr[i]=-1;
        _mc_stable_isoverlay[i]=-1;
      }
      _mc_stable_n=0;
      _mc_stable_y12=0;
      _mc_stable_y23=0;
      _mc_stable_d12=0;
      _mc_stable_d23=0;

      for(int i=0; i<2; i++) {
        _mc_stable_jet_E[i]=0;
        _mc_stable_jet_px[i]=0;
        _mc_stable_jet_py[i]=0;
        _mc_stable_jet_pz[i]=0;
      }


      // RECONSTRUCTED EVENT
      _y12=0;
      _y23=0;
      _d12=0;
      _d23=0;
      _oblateness=0;
      _aplanarity=0;
      _major_thrust_value=0;
      _minor_thrust_value=0;
      _principle_thrust_value=0;
      _sphericity=0;
      
      for(int i=0; i<3; i++ ) {
	_major_thrust_axis[i]=0;
	_minor_thrust_axis[i]=0;
	_principle_thrust_axis[i]=0;
	_sphericity_tensor[i]=0;
      }

      _pfo_n=0;
      _nvtx=0;
      _pfo_n_j1=0;
      _nvtx_j1=0;
      _pfo_n_j2=0;
      _nvtx_j2=0;

      for(int ipfo=0; ipfo<1000; ipfo++) {  

	_pfo_jet_match[ipfo]=-1;

	_pfo_E[ipfo]=0; 
	_pfo_px[ipfo]=0;
	_pfo_py[ipfo]=0;
	_pfo_pz[ipfo]=0;
	_pfo_m[ipfo]=0;
	_pfo_type[ipfo]=0;
	_pfo_charge[ipfo]=-1000;
        _pfo_charge[ipfo]=0;
	_pfo_pdgcheat[ipfo]=-1000;
	_pfo_isisr[ipfo]=-1;
	_pfo_isoverlay[ipfo]=-1;
	_pfo_istrack[ipfo]=-1;
	_pfo_vtx[ipfo]=-1;
	  
	_pfo_tpc_hits[ipfo]=0;
	_pfo_dedx[ipfo]=0;
	_pfo_dedxerror[ipfo]=0;
	_pfo_d0[ipfo]=0;
	_pfo_d0error[ipfo]=0;
	_pfo_z0[ipfo]=0;
	_pfo_z0error[ipfo]=0;
	_pfo_omega[ipfo]=0;
	_pfo_omegaerror[ipfo]=0;
	_pfo_phi[ipfo]=0;
	_pfo_phierror[ipfo]=0;
	_pfo_tanlambda[ipfo]=0;
	_pfo_tanlambdaerror[ipfo]=0;
	_pfo_chi2[ipfo]=0;
	_pfo_ndf[ipfo]=0;
	
	_pfo_pid[ipfo]=0;
	_pfo_pid_likelihood[ipfo]=0;
	_pfo_piddedx[ipfo]=0;
	_pfo_piddedx_likelihood[ipfo]=0;
	
      }
      
    }//end clear
  };//end StatsData_QQbar	
  
}
#endif
