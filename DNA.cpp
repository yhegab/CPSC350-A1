#include "DNA.h"

DNA::DNA(){
  m_fname = "";
}

DNA::DNA(string fname){
  m_fname = fname;
  m_A = 0;
  m_G = 0;
  m_C = 0;
  m_T = 0;
  m_sum = 0;
  m_lines = 0;
  m_mean = 0;
  m_variance = 0;
}

DNA::~DNA(){
  cout << "Program has been deleted" << endl;
}


int main(int argc, char **argv){
  DNA* dnaPointer;
  //cout << lengthof(argv) << endl;
  //if(sizeof(argv) == 2){
    string filename = argv[2];
    cout << filename << endl;
    while(filename != "q"){
    DNA sample(filename);
    dnaPointer = &sample;
    if(dnaPointer->readFile() == 1){
      return 1;
    };
    dnaPointer->writeFile();
    cout << "If you would like to process another file, please enter the name. Otherwise enter q to quit: ";
    cin >> filename;
  }
    //}
//  else
  //  cout << "invalid argument passed: must enter file name" << endl;
return 0;
}


int DNA::readFile(){
  ifstream inFS;
  ifstream inFS2;
  bool valid;
  string DNALine;
  int AG = 0;
  int AC = 0;
  int AT = 0;
  int TA = 0;
  int TC = 0;
  int TG = 0;
  int GC = 0;
  int GT = 0;
  int GA = 0;
  int CT = 0;
  int CA = 0;
  int CG = 0;
  int CC = 0;
  int TT = 0;
  int AA = 0;
  int GG = 0;
  inFS.open(m_fname);
  cout << "inFS opened" << endl;
  if(!inFS.is_open()){
    return 1;
  }
while(!inFS.eof()){
//  cout << "Loop iterate" << endl;
//mustmakeuppercase
inFS >> DNALine;
//cout << "DNA LINE: " << DNALine << endl;
    for(int i = 0; i < DNALine.length(); ++i){
      valid = true;
      string char1 = DNALine.substr(i, 1);
      string char2 = DNALine.substr(i+1, 1);
      string chunk = DNALine.substr(i,2);
      //make a helper method for this check
      if(char1 == "A" || char1 == "a"){m_A++;}
      else if(char1 == "T" || char1 == "t"){m_T++;}
      else if(char1 == "G" || char1 == "g"){m_G++;}
      else if(char1 == "C" || char1 == "c"){m_C++;}
      else{
        valid = false;
        break;
      }

      if(char2 == "A" || char2 == "a"){m_A++;}
      else if(char2 == "T" || char2 == "t"){m_T++;}
      else if(char2 == "G" || char2 == "g"){m_G++;}
      else if(char2 == "C" || char2 == "c"){m_C++;}
      else{
        valid = false;
        break;
      }

      if(chunk == "AT"){AT++;}
      else if(chunk == "AG"){AG++;}
      else if(chunk == "AC"){AC++;}
      else if(chunk == "AA"){AA++;}
      else if(chunk == "TA"){TA++;}
      else if(chunk == "TG"){TG++;}
      else if(chunk == "TC"){TC++;}
      else if(chunk == "TT"){TT++;}
      else if(chunk == "GA"){GA++;}
      else if(chunk == "GC"){GC++;}
      else if(chunk == "GT"){GT++;}
      else if(chunk == "GG"){GG++;}
      else if(chunk == "CA"){CA++;}
      else if(chunk == "CG"){CG++;}
      else if(chunk == "CT"){CT++;}
      else if(chunk == "CC"){CC++;}
      else{
        cout << "Invalid DNA String" << endl;
        valid = false;
        break;
      }
      if(++i >= DNALine.length()){
        break;
      }

    }
    if(valid){
    m_sum += DNALine.length();
    m_lines++;
  }
}
m_mean = m_sum/m_lines;

  float meansq = m_mean * m_mean;
  inFS.close();
  inFS2.open(m_fname);
  while(!inFS2.eof()){
    inFS2 >> DNALine;
    m_variance += meansq - pow(DNALine.size(), 2);
  }
inFS2.close();
m_variance /= (m_lines - 1);
m_variance = abs(m_variance);
return 0;
}

void DNA::writeFile(){
  srand(time(NULL));
  float stddev = sqrt(m_variance);
  ofstream outFS;
  outFS.open("YoussefHegab.txt", ios::app);
  outFS << "Youssef Hegab \nStudent ID: 2312131 \nSection 1\n";
  outFS << "DNA Report:" << endl;
  outFS << "Sum: " << m_sum << endl;
  outFS << "Number of Lines: " << m_lines << endl;
  outFS << "Mean: " << m_mean << endl;
  outFS << "Variance: " << m_variance << endl;
  outFS << "Standard Deviation: " << stddev << endl << endl;
  outFS << "Number of Gs: " << m_G << endl;
  outFS << "Number of Cs: " << m_C << endl;
  outFS << "Number of Ts: " << m_T << endl;
  outFS << "Number of As: " << m_A << endl;
 outFS << "Sample DNA strings with the same gaussian distribution as the previous set:" << endl;
 float a = 0;
 float b = 0;
 float X = 0;
 a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 X = sqrt(-2 * log(a)) * cos(2*M_PI *b);
 int testG = m_G;
 int testC = m_C+testG;
 int testT = m_T+testC;
 int testA = m_A+testT;
 float test;
 outFS << endl;
 int lengthofstring = 0;
 for(int j = 0; j < 1000; j++){
   a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
   b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
   X = sqrt(-2 * log(a)) * cos(2*M_PI *b);
   lengthofstring = static_cast <int> ((X*stddev) + m_mean);
   if(lengthofstring <= 0){
     lengthofstring = m_mean;
   }
   for(int k = 0; k < lengthofstring; k++){
     test = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
     test *= m_sum;
     test *= 2;

     if(test <= testG){
       outFS << "G";
     }
     else if(test <= testC){
       outFS << "C";
     }
     else if(test <= testT){
       outFS << "T";
     }
     else if(test <= testA){
       outFS << "A";
     }
   }
   outFS << endl;
 }
 outFS << endl << endl << endl;
 outFS.close();
}
