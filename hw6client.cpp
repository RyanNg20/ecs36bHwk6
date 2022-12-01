
// ecs36b first program

#include <iostream>
#include "ecs36b_Exception.h"
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>


// JSON RPC part
#include "hw6client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

string possibleguesses[100];
int pguess = 100;
int countguess = 0;

string badletter = "abcdefghijklmnopqrstuvwxyz"; 
ifstream fpSol("./lists/SOLUTION.TXT");


bool isValid(string word){
     for(int i = 0; i < 5;i ++){
        if (badletter[word[i] - 'a'] == '_'){
          return false;
     }  
   }
   return true;
}

 void parse(){
      string s; 
   while (getline(fpSol,s)){
    
      if (isValid(s)){
        cout << s + "\n";
        
        possibleguesses[countguess] = s;
        countguess += 1;
      }
            
     }

}


void removeWord(string posstr, string word){
  for(int i = 0; i < 5 ; i++){
    if (posstr[i] == '_'){
      badletter[word[i] - 'a'] = '_';
    }
  }
}

int
main()
{
  // distributed wordle demo for 11/23/2022
  HttpClient httpclient("http://127.0.0.1:8384");
  // HttpClient httpclient("https://2ada-73-66-168-157.ngrok.io/");
  hw6Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value jv_list;


      try {
    myv = myClient.obtain("obtain", "Wordle", "00000000");
    } catch (JsonRpcException &e) {
      cerr << e.what() << endl;
  }
    std::cout << myv.toStyledString() << std::endl;

  try{
  myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "brick");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }
          std::cout << myv.toStyledString() << std::endl;


  try{
  myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "jumpy");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }
          std::cout << myv.toStyledString() << std::endl;


  try{
  myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "glent");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }
          std::cout << myv.toStyledString() << std::endl;


  try{
  myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "vozhd");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }
          std::cout << myv.toStyledString() << std::endl;


  try{
  myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "waqfs");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }
          std::cout << myv.toStyledString() << std::endl;

  for (int i = 0; i < 5; i ++){
      removeWord(myv["guesses"]["data"][i]["result"].asString(), myv["guesses"]["data"][i]["guess"].asString()); 
  }

  cout << badletter;
  parse();
  int counter;
  counter = 0;
    while (myv["check_word"] != "#####"){
      try{
  myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     possibleguesses[counter]);
        counter += 1;
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }
  }
            std::cout << myv.toStyledString() << std::endl;

    try {
    // worry
    myv = myClient.submit("submit", myv["game_id"].asString(), "Nobody");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  return 0;
}
