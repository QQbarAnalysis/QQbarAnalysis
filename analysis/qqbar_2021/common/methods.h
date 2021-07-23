
using namespace std;

float getModule(vector< float > & v)   {
  float module = 0.0;
  for (unsigned int i = 0; i < v.size(); i++) module += v[i]*v[i];
  module = sqrt(module);
  return module;
}
   
std::vector< float > getDirection(vector<float> & vectorPoint) {
  vector< float > vector1;
  float module = getModule(vectorPoint);
  for (int i = 0; i < 3; i++) vector1.push_back( vectorPoint[i]/module);
  return vector1;
}
   
std::vector< float > getAngles(std::vector< float > & direction) {
  vector< float > result;

  TLorentzVector v1(direction[0],direction[1],0,0);
  TLorentzVector v2(1,0,0,0);
     
  float phi = v1.Angle(v2.Vect()); 
  if(direction[1]<0 && direction[0]>0) phi=2*TMath::Pi() - phi;
  if(direction[1]<0 && direction[0]<0) phi=2*TMath::Pi() - phi;
    
  if(direction[1]<0 && direction[0]==0) phi=3.*TMath::Pi()/2.;
  if(direction[1]>0 && direction[0]==0) phi=TMath::Pi()/2.;
  if(direction[1]==0 && direction[0]>0) phi=0;
  if(direction[1]==0 && direction[0]<0) phi=TMath::Pi();
    
  float teta = acos(direction[2]);
  result.push_back(phi);
  result.push_back(teta);
  return result;
}

std::vector< float > CalculateAnglesMom(float px, float py, float pz) {
  std::vector<float> p;
  p.push_back(px);
  p.push_back(py);
  p.push_back(pz);
  std::vector< float > direction = getDirection(p);
  std::vector< float > angles=getAngles(direction);
  angles.push_back(sqrt(px*px+py*py+pz*pz));
  return angles;
}

std::vector< float > CalculateAngles(float px, float py, float pz) {
  std::vector<float> p;
  p.push_back(px);
  p.push_back(py);
  p.push_back(pz);
  std::vector< float > direction = getDirection(p);
  std::vector< float > angles=getAngles(direction);
  return angles;
}
   
float GetCostheta(std::vector<float> & vectorPoint){
  float costheta1 =  -2.0;
  std::vector< float > d1= getDirection(vectorPoint);
  costheta1 =  std::cos( getAngles(d1).at(1) );
  return costheta1;
}

float GetCosphi(std::vector<float> & vectorPoint){
  float cosphi= -2.0;
  std::vector<float> d1 = getDirection(vectorPoint);
  cosphi = std::cos(getAngles(d1).at(0));
  return cosphi;
}

float GetSinacol(TVector3 v1, TVector3 v2){
  float sinacol =  -2.0;
  TVector3 v= v1.Cross(v2);
  sinacol = (v.Mag()/(v1.Mag()*v2.Mag()));// * v2.Mag()/(v1+v2).Mag(); 
  return sinacol;
}

float getAngle2Vec(float px1, float py1, float pz1, float E1, float px2, float py2, float pz2, float E2) {

  TLorentzVector v1(px1,py1,pz1,E1);
  TLorentzVector v2(px2,py2,pz2,E2);
     
  Double_t a = v1.Angle(v2.Vect());  // get angle between v1 and v2
  return a;
}
   
