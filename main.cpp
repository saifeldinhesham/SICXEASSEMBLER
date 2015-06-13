#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;
const int linesize = 100;
const int tokensize =34;
const char* const space= " "; //in strtkn
int flagerror=0;
int st=0;
int ed=0;
int loc=0;
char buf[linesize];
ifstream fin ("pass1.txt");
ofstream fout("listfile.txt");
map<string,string>m1;
map<string,int>m2;
unordered_multimap<string,int>lb;
void  checkopcode(string opcode,string oprand,string label);
void printlabel(string label);
void chlabel(string label);
void addlabel(string label);
void printopcode(string opcode);
void suggest_correction(string test);
void checkoprand(string oprand);
int main()
{
    
    string label;
string opcode;
string oprand;
//hashtable mnmonic(key),opcode
m1["RMO"]="AC";m1["LDA"]="00";m1["LDB"]="68";m1["LDF"]="70";m1["LDL"]="08";m1["LDS"]="6C";m1["LDT"]="74";m1["LDX"]="04";m1["STA"]="0C";m1["STB"]="78";m1["STF"]="80";m1["STL"]="14";
m1["STS"]="7C";m1["STT"]="84";m1["STX"]="10";m1["LDCH"]="50";m1["STCH"]="54";m1["ADD"]="18";m1["SUB"]="1C";m1["MUL"]="20";m1["DIV"]="24";m1["ADDR"]="90";m1["SUBR"]="94";m1["MULR"]="98";
m1["DIVR"]="9C";m1["COMP"]="28";m1["COMPR"]="A0";m1["J"]="3C";m1["JEQ"]="30";m1["JGT"]="34";m1["JLT"]="38";m1["TIX"]="2C";m1["TIXR"]="B8";m1["JSUB"]="48";m1["RSUB"]="4C";
//hashtable  mnemonic(key),format
m2["RMO"]=2;m2["LDA"]=3;m2["LDB"]=3;m2["LDF"]=3;m2["LDL"]=3;m2["LDS"]=3;m2["LDT"]=3;m2["LDX"]=3;m2["STA"]=3;m2["STB"]=3;m2["STF"]=3;m2["STL"]=3;
m2["STS"]=3;m2["STT"]=3;m2["STX"]=3;m2["LDCH"]=3;m2["STCH"]=3;m2["ADD"]=3;m2["SUB"]=3;m2["MUL"]=3;m2["DIV"]=3;m2["ADDR"]=2;m2["SUBR"]=2;m2["MULR"]=2;
m2["DIVR"]=2;m2["COMP"]=3;m2["COMPR"]=2;m2["J"]=3;m2["JEQ"]=3;m2["JGT"]=3;m2["JLT"]=3;m2["TIX"]=3;m2["TIXR"]=2;m2["JSUB"]=3;m2["RSUB"]=3;

cout<<"     ****** PROGRAM LISTING ******      "<<endl;
fout<<"     ****** PROGRAM LISTING ******      "<<endl;
cout<<"\n";
fout<<"\n";
  if(fin.is_open()){

  while (!fin.eof())
  {

fin.getline(buf,linesize);
int n = 0;
const char* token[tokensize] = {};
string str(buf);
token[0] = strtok(buf,space);

if(strncmp(buf,".",1)==0){

cout<<"        "<<str<<endl;
fout<<"        "<<str<<endl;
    continue;
}
if (token[0])
      for (n = 1; n < tokensize; n++)
      {
        token[n] = strtok(0,space);
        if (!token[n])
            break;
      }
      switch(n){
  case 2:
    opcode=token[0];
    oprand=token[1];
    checkopcode(opcode,oprand," ");
    break;
    case 3:
label=token[0];
opcode=token[1];
oprand=token[2];
checkopcode(opcode,oprand,label);
break;

    default:
        flagerror=1;
        cout<<buf<<endl;
        cout<<"        ***ERROR100 EMPTY LINE OR INVALID  INSTRUCTION***"<<endl;
        fout<<buf<<endl;
        fout<<"        ***ERROR100 EMPTY LINE OR INVALID INSTRUCTION***"<<endl;
        break;

      }
    }
    if(ed==0){
flagerror=1;
        cout<<"**ERROR109 NO END  FOUND"<<endl;
         fout<<"**ERROR109 NO END  FOUND"<<endl;
         flagerror=0;
    }
    fin.close();

  }else{
      flagerror=1;
      cout<<"*** ERROR101 PASS1 IS NOT FOUND\n";
      fout<<"***ERROR 101 PASS1 IS NOT FOUND\n";
  }
  cout<<"\n";
  fout<<"\n";
  if(flagerror==0){
  cout<<"     ***SYMBOL TABLE***    "<<endl;
  fout<<"     ***SYMBOL TABLE***    "<<endl;
  cout<<"\n";
  fout<<"\n";

  for (auto &x:lb){

         cout << "     " << x.first;
         fout<< "     " << x.first;
     printlabel(x.first);
     cout<<"  ";
    cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<x.second<<endl;
    fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<x.second<<endl;
  }
  cout<<"***************SUCCESSFUL PASS 1************************"<<endl;
  fout<<"***************SUCCESSFUL PASS 1************************"<<endl;
fout.close();

}else{
    cout<<"**************UNSUCCESSFUL PASS 1*********************"<<endl;
    fout<<"**************UNSUCCESSFUL PASS 1*********************"<<endl;
}
int close;
cout << "Press any key then enter to close..." << endl;
cin >> close;
return 0;
}
//*****************END OF MAIN*********************************

void  checkopcode( string opcode,string oprand,string label){
    transform(opcode.begin(), opcode.end(),opcode.begin(), ::toupper);
    transform(label.begin(),label.end(),label.begin(),::toupper);
    transform(oprand.begin(),oprand.end(),oprand.begin(),::toupper);



if(opcode.compare("END")!=0){     //nested if

    if (m2.count(opcode)) {//Comparing opcode with in map

if(m2[opcode]==2){
    if((oprand.size()!=3)||(oprand[1]!=',')){
            cout<<"***ERROR 112 WRONG OPERAND FORMAT"<<endl;
            fout<<"***ERROR 112 WRONG OPERAND FORMAT"<<endl;
        flagerror=1;
    }
}
        int len;
        addlabel(label);
        cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        printlabel(label);
       cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);

        len=m2[opcode];
        loc=loc+len;
chlabel(label);
if((st==0)||(ed==1)){
        flagerror=1;
            cout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
            fout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END"<<endl;
        }
           }else{//

    if(opcode=="START"){
            if((opcode=="START")&&(st==0)){
    st=1;
         addlabel(label);
       chlabel(label);
        stringstream start;
        start<< std::hex <<oprand;
        start>>loc;//integer value
         cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;//hexa value
         fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;//hexa value
       printlabel(label);
       cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);

        }else{
        cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;//hexa value
         fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;//hexa value
       printlabel(label);
       cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
flagerror=1;
        cout<<" ****ERROR103 START IS DEFINED BEFORE"<<endl;
        fout<<" ****ERROR103 START IS DEFINED BEFORE"<<endl;
        }

    }else { //
    if(opcode=="WORD"){
        addlabel(label);
        cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
       printlabel(label);
      cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
        loc=loc+3;
        chlabel(label);
        if((st==0)||(ed==1)){
                flagerror=1;
            cout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
            fout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
        }

    }else{ //
        if(opcode=="RESW"){
             addlabel(label);
                cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
                fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
               printlabel(label);
cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
int value=atoi(oprand.c_str());
        loc=loc+(3*value);
         chlabel(label);
         if((st==0)||(ed==1)){
                flagerror=1;
            cout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
            fout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END"<<endl;
        }
        }else{ //
            if(opcode=="RESB"){
                addlabel(label);
                int value=atoi(oprand.c_str());
               cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
               fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
               printlabel(label);
cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
       loc=loc+value;
        chlabel(label);
        if((st==0)||(ed==1)){
                flagerror=1;
            cout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END"<<endl;
            fout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END"<<endl;
        }
            }
            else{ //
                    int b;
                if(opcode=="BYTE"){
                        if(oprand[0]=='C'){
                   addlabel(label);
                        b=oprand.size();
                    b=b-3;
                     cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
                    fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
printlabel(label);

 cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
           loc=loc+b;
        chlabel(label);
        if((st==0)||(ed==1)){
                flagerror=1;
            cout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
            fout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
        }
                        }else{
                            if(oprand[0]=='X'){
                                 addlabel(label);
                         b=oprand.size();
                    b=b-3;
                    if(b%2!=0){
                            flagerror=1;
                      cout<<"**ERROR 111 WRONG HEXA VALUE"<<endl;
                      fout<<"**ERROR 111 WRONG HEXA VALUE"<<endl;
                    }
                    b=b/2;
                     cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
                    fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
printlabel(label);

 cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
           loc=loc+b;
        chlabel(label);
        if((st==0)||(ed==1)){
                flagerror=1;
            cout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
            fout<<" ***ERROR102 MUST BEGIN AFTER START OR YOU COMPLETED AFTER END "<<endl;
        }
                            }else{
                             flagerror=1;
                            cout<<"***ERROR 110 UNDEFINED REFERENCE TO OPERAND"<<endl;
                            fout<<"***ERROR 110 UNDEFINED REFERENCE TO OPERAND"<<endl;
                            }

}


                }
else{ //

        if(opcode[0]=='+'){ //format 4 to location
string comp=opcode.substr(1);
                if(m2.count(comp)){
                    if(m2[comp]==3){
                           int len;
        addlabel(label);
        cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        printlabel(label);
cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
       len=4;
        loc=loc+len;
chlabel(label);
if(st==0){
        flagerror=1;
            cout<<" ***ERROR103 MUST BEGIN AFTER START "<<endl;
            fout<<" ***ERROR103 MUST BEGIN AFTER START "<<endl;
        }
}else{
     cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
     fout<<cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
     printlabel(label);
cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);
flagerror=1;
cout<<"***ERROR104 INVALID1 MNMEMOIC INSTRUCTION"<<endl;
   fout<<"***ERROR104 INVALID MNMEMOIC INSTRUCTION"<<endl;

                }
                }
}
else{  //
        if(opcode=="BASE"){
                         addlabel(label);
       chlabel(label);
       cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;//hexa value
         fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;//hexa value
       printlabel(label);
       cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);

        }else{
     cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
     fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
    printlabel(label);

   cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
cout<<"***ERROR104 INVALID MNMEMOIC INSTRUCTION"<<endl;
   fout<<"***ERROR104 INVALID MNMEMOIC INSTRUCTION"<<endl;
   flagerror=1;
    suggest_correction(opcode);

    }
}
}
            }
}
    }
    }
    }
}

if(opcode=="END"){
        if((opcode=="END")&&(ed==0)){
                ed=1;
    int len;
        addlabel(label);
        cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        printlabel(label);
       cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        checkoprand(oprand);

        len=m2[opcode];
        loc=loc+len;
chlabel(label);
        }else{
         cout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        fout<<std::setfill ('0') << std::setw(5) << std::uppercase<<std::hex<<loc<<"   "<<label;
        printlabel(label);
       cout<<opcode;
        fout<<opcode;
        printopcode(opcode);
        cout<<oprand<<endl;
        fout<<oprand<<endl;
        cout<<" ***ERROR105 END IS DEFINED BEFORE"<<endl;
        fout<<" ***ERROR105 END IS DEFINED BEFORE"<<endl;
flagerror=1;
        }
}

}
//function to display
void printlabel(string label){
if(label.size()>8){
            cout<<label<<"***ERROR106 LABEL SIZE OVER"<<endl;
            fout<<label<<"***ERROR106 LABEL SIZE OVER"<<endl;
            flagerror=1;
        }else{
        int i=8-label.size();
        for(int j=-1;j<i;j++){
           cout<<" ";
           fout<<" ";
        }
}
}

//repeated label
void chlabel(string label){
int x=lb.count(label);

if(x>1){
        flagerror=1;
    cout<<label<<" IS DEFINED BEFORE ***ERROR107"<<endl;
    fout<<label<<" IS DEFINED BEFORE ***ERROR 107"<<endl;
}
}
//adding label to map
void addlabel(string label){
if(label==" "){

        }else{
lb.emplace(label,loc);
        }
}
void printopcode(string opcode){

        int i=8-opcode.size();
        for(int j=0;j<i;j++){
           cout<<" ";
           fout<<" ";
        }

}
void suggest_correction(string test){

    int i,j,m=0,flag=0;
    vector <string> v2,v3,v4,v5,v6;
    vector<string> v = {"RMO", "LDA" , "LDB" , "LDF" , "LDL" , "LDS" , "LDT" , "LDX" , "STA" , "STB" , "STF" , "STL" ,"STS"
    ,"STT" , "STX" , "LDCH" ,"STCH" , "ADD" , "SUB","MUL" , "DIV" , "ADDR","SUBR" , "MULR" , "DIVR" , "COMP", "COMPR", "JEQ", "JGT",
     "JLT", "TIX", "TIXR", "JSUB", "RSUB"};

    string result = "";

        for (i=0;i<v.size();i++){
        if (test.size() == v[i].size()){
            v2.push_back(v[i]);
        }
    }

        for (i=0;i<v2.size();i++){
            for(j=0;j<v2[i].size();j++)
                if (test[m] == v2[i][j])
                  v3.push_back(v2[i]);
    }
            for (i=0;i<v3.size();i++)
            //cout << "v3 "<< v3[i] << endl;

if (v3.size() == 1){
    result = v3[0];
    flag = 1;
    }  else if (v3[1] == v3[2]) {
        result = v3[1];
        flag = 1;
    }

if (flag != 1){
        m++;
        for (i=0;i<v3.size();i++){
            for(j=0;j<v3[i].size();j++)
                if (test[m] == v3[i][j])
                  v4.push_back(v3[i]);
        }

                for (i=0;i<v4.size();i++)
            //cout << "v4 "<< v4[i] << endl;

    if (v4.size() == 1){
    result = v4[0];
    flag = 1;
    }  else if (v4[1] == v4[2]) {
        result = v4[1];
        flag = 1;
    }
}

if (flag != 1){
        m++;
        for (i=0;i<v4.size();i++){
            for(j=0;j<v4[i].size();j++)
                if (test[m] == v4[i][j])
                  v5.push_back(v4[i]);
        }
for (i=0;i<v5.size();i++)
            //cout << "v5 "<< v5[i] << endl;
if (v5.size() == 1){
    result = v5[0];
    flag = 1;
    } else if (v5[1] == v5[2]){
        result = v5[1];
        flag = 1;
    }
}

if (flag != 1){
        m++;
        for (i=0;i<v5.size();i++){
            for(j=0;j<v5[i].size();j++)
                if (test[m] == v5[i][j] && test[m]!= test[m-1])
                  v6.push_back(v5[i]);
        }
        for (i=0;i<v6.size();i++)
            //cout << "v6 "<< v6[i] << endl;
if(v6.size() == 1)
    {
       result = v6[0];
    }
    else if(v6.size() == 2)
    {
       result = "SUBR or RUSB";
    }
}
cout << " **YOU ENTERED : " << test << endl;
fout<<"  **YOU ENTERED : " << test << endl;
if (result == ""){
cout << "       **NO SUGGESTIONS FOR CORRECTION !!" << endl;
fout<< "       **NO SUGGESTIONS FOR CORRECTION !!" << endl;
}else{
cout << "       **SUGGESTED CORRECTION: " << result << endl;
fout<< "       **SUGGESTED CORRECTION: " << result << endl;
    }
}
void checkoprand(string oprand){

if(oprand.size()>18){
flagerror=1;
    cout<<"***ERROR 108 OPERAND OVER FLOW"<<endl;
    fout<<"***ERROR 108 OPERAND OVER FLOW"<<endl;
}

}
