#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct book {
  string asin;
  string title;
};

string changeToCSV(vector<book> A){
  string s = "asin,title\n";
  for(int i = 0; A.size() > i; i++){
    s += A[i].asin + "," + A[i].title + "\n";
  }
  return s;
}

int main(int argc, char *argv[]){
  ifstream ifs(argv[1]);
  if (ifs.fail()){
    cout << "could not open the input file, put KindleSyncMetadataCache.xml" << endl;
    return 0;
  }
  string s = "";
  getline(ifs, s);
  int depth = 0;
  int inBracket = 0;
  int capture = 0;
  string asin = "";
  string title = "";
  string tmp = "";
  vector<book> data;
  for(int i = 0; s.size() > i; i++){
    if(s[i] == '<'){
      if(capture == 1){
        asin = tmp;
      }else if (capture == 2){
        title = tmp;
        if(title != "---------------")data.push_back({asin,title});
      }
      tmp = "";
      capture = 0;

      if(s[i+1] == '/'){
        inBracket = 1;
        i++;
      }else{
        inBracket = 2;
        if(s.substr(i+1,4) == "ASIN"){capture = 1;}
        if(s.substr(i+1,5) == "title"){capture = 2;}
      }
      continue;
    }
    if(s[i] == '>'){
      if(inBracket == 1){
        depth--;
      }else{
        depth++;
      }
      inBracket = 0;
      tmp = "";
      continue;
    }
    if(!inBracket && capture){
      tmp.push_back(s[i]);
    }

  }
  assert(depth == 0);
  ofstream ofs;
  ofs.open("output.csv", ios::out);
  ofs << changeToCSV(data) << endl;
  ofs.close();
  return 0;
}
