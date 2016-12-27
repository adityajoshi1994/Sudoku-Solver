#include <iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include <chrono>
#include<string.h>
#include<map>

using namespace std;
using namespace std::chrono;
int isValidSudoku(vector<vector<int> >adjlist);
//int lcv(vector<vector<int> >adjlist, int index, map<int, int> &lcValMap);
int lcv(vector<vector<int> >adjlist, int index, vector<int> &lcVal);


int prob[9] = {0};

int numberOfBacktrack = 0;

//7 0 3 0 0 1 0 9 4 0 0 1 0 0 4 6 0 7 0 0 0 5 0 7 0 0 3 0 0 7 0 6 0 8 0 5 0 2 8 0 0 0 3 6 0 4 0 5 0 1 0 9 0 0 5 0 0 1 0 6 0 0 0 1 0 6 4 0 0 5 0 0 2 7 0 8 0 0 4 0 6
//8 0 0 0 0 0 0 0 5 0 2 0 9 0 0 0 0 8 0 0 0 8 6 7 0 1 0 0 1 0 7 0 0 3 0 0 0 0 2 0 8 0 9 0 0 0 0 4 0 0 6 0 8 0 2 4 6 3 5 0 0 0 0 5 0 0 6 0 4 0 2 0 1 0 0 0 7 0 0 0 6

int MRV(vector<vector<int> >& adjlist, vector<vector<int> >board){
    int min=INT_MAX;
    int index=INT_MAX;
    for(int i=0;i<adjlist.size();i++){
        int row=i/9;
        int column=i%9;
        //        if(adjlist[i].size()>1){
        if(board[row][column]==0){
            if(adjlist[i].size() == 1) {
                index = i;
                break;
            }
            if(min>adjlist[i].size()){
                min=adjlist[i].size();
                index=i;
            }
        }
    }
    return index;
}



//// MRV with MD
//int MRV(vector<vector<int> >& adjlist, vector<vector<int> >board){
//    int min=INT_MAX;
//    int index=INT_MAX;

//    vector<int> minIndex;

//    for(int i=0;i<adjlist.size();i++){
//        int row=i/9;
//        int column=i%9;
//        //        if(adjlist[i].size()>1){
//        if(board[row][column]==0){
//            //            if(adjlist[i].size() == 1) {
//            //                index = i;
//            //                break;
//            //            }
//            if(min>adjlist[i].size()){
//                min=adjlist[i].size();
//                index=i;
//                minIndex.clear();
//                minIndex.push_back(i);
//            } else if(min == adjlist[i].size())
//                minIndex.push_back(i);
//        }
//    }

//    int max = 0;

//    //MD
//    while(minIndex.size()!=0) {
//        int temp = minIndex.back();
//        minIndex.pop_back();
//        int row = temp/9;
//        int column = temp%9;

//        int count=0;
//        for(int k=0;k<9;k++){
//            if(k!=column){
//                if(board[row][k] == 0){
//                    count++;
//                }
//            }
//        }
//        for(int k=0;k<9;k++){
//            if(k!=row){
//                if(board[k][column] == 0){
//                    count++;
//                }
//            }
//        }
//        int subboardi=row/3;
//        int subboardj=column/3;
//        for(int m=subboardi*3;m<subboardi*3+3;m++){
//            for(int n=subboardj*3;n<subboardj*3+3;n++){
//                if(m!=row && n!=column){
//                    if(board[m][n] == 0){
//                        count++;
//                    }
//                }
//            }
//        }

//        if(count>=max) {
//            max = count;
//            index = temp;
//        }
//    }


//    return index;
//}


int prune(vector<vector<int> >&adjlist,int row,int column,int key, vector<vector<int> >&board){
    for(int i=0;i<adjlist[9*row+column].size();i++){
        adjlist[9*row+column].clear();
        adjlist[9*row+column].push_back(key);
    }
    board[row][column] = key;

    int inconsistencyCheckArr[9] = {0};
    int numberOfUniassignedVar = 0;

    for(int k=0;k<9;k++){
        if(k!=column){
            if(find(adjlist[9*row+k].begin(),adjlist[9*row+k].end(),key)!=adjlist[9*row+k].end() && board[row][k]==0){
                //            if(board[row][k]==0){
                adjlist[9*row+k].erase(std::remove(adjlist[9*row+k].begin(), adjlist[9*row+k].end(), key), adjlist[9*row+k].end());
            }
            //            if(adjlist[9*row+k].size()==1 && board[row][k]==0){
            ////                board[row][k] = adjlist[9*row+k][0];
            //                int suc = prune(adjlist, row, k, adjlist[9*row+k][0], board);
            //                if(suc == -1)
            //                    return -1;
            //            }
            if(adjlist[9*row+k].size()==0){
                return -1;
            }
            //incons check
            if(board[row][k] == 0){
                numberOfUniassignedVar++;
                for(int i=0;i<adjlist[9*row+k].size();i++)
                    if(inconsistencyCheckArr[adjlist[9*row+k][i]-1]==0)
                        inconsistencyCheckArr[adjlist[9*row+k][i]-1] = 1;
            }

        }
    }

    //Incons check
    int distinctValues=0;
    for(int t = 0;t<9;t++)
        distinctValues += inconsistencyCheckArr[t];

    if(distinctValues<numberOfUniassignedVar)
        return -1;
    memset(inconsistencyCheckArr, 0, 9*sizeof(int));
    numberOfUniassignedVar = 0;

    // remove from column elements
    for(int k=0;k<9;k++){
        if(k!=row){
            if(find(adjlist[9*k+column].begin(),adjlist[9*k+column].end(),key)!=adjlist[9*k+column].end() && board[k][column]==0){
                //            if(board[k][column]==0){
                adjlist[9*k+column].erase(std::remove(adjlist[9*k+column].begin(), adjlist[9*k+column].end(), key), adjlist[9*k+column].end());
            }
            //            if(adjlist[9*k+column].size()==1 && board[k][column]==0){
            ////                board[k][column] = adjlist[9*k+column][0];
            //                int suc = prune(adjlist, k, column, adjlist[9*k+column][0], board);
            //                if(suc == -1)
            //                    return -1;
            //            }
            if(adjlist[9*k+column].size()==0){
                return -1;
            }

            //incons check
            if(board[k][column] == 0){
                numberOfUniassignedVar++;
                for(int i=0;i<adjlist[9*k+column].size();i++)
                    if(inconsistencyCheckArr[adjlist[9*k+column][i]-1]==0)
                        inconsistencyCheckArr[adjlist[9*k+column][i]-1] = 1;
            }

        }
    }

    //Incons check
    distinctValues=0;
    for(int t = 0;t<9;t++)
        distinctValues += inconsistencyCheckArr[t];

    if(distinctValues<numberOfUniassignedVar)
        return -1;
    memset(inconsistencyCheckArr, 0, 9*sizeof(int));
    numberOfUniassignedVar = 0;




    // remove from box elements
    int subboardi=row/3;
    int subboardj=column/3;
    for(int m=subboardi*3;m<subboardi*3+3;m++){
        for(int n=subboardj*3;n<subboardj*3+3;n++){
            if(m!=row && n!=column){
                if(find(adjlist[9*m+n].begin(),adjlist[9*m+n].end(),key)!=adjlist[9*m+n].end() && board[m][n]==0){
                    //                if(board[m][n]==0){
                    adjlist[9*m+n].erase(std::remove(adjlist[9*m+n].begin(), adjlist[9*m+n].end(), key), adjlist[9*m+n].end());
                }
                //                if(adjlist[9*m+n].size()==1 && board[m][n]==0){
                ////                    board[m][n] = adjlist[9*m+n][0];
                //                    int suc = prune(adjlist, m, n, adjlist[9*m+n][0], board);
                //                    if(suc == -1)
                //                        return -1;
                //                }
                if(adjlist[9*m+n].size()==0){
                    return  -1;
                }

                //incons check
                if(board[m][n] == 0){
                    numberOfUniassignedVar++;
                    for(int i=0;i<adjlist[9*m+n].size();i++)
                        if(inconsistencyCheckArr[adjlist[9*m+n][i]-1]==0)
                            inconsistencyCheckArr[adjlist[9*m+n][i]-1] = 1;
                }

            }
        }
    }

    //Incons check
    distinctValues=0;
    for(int t = 0;t<9;t++)
        distinctValues += inconsistencyCheckArr[t];

    if(distinctValues<numberOfUniassignedVar)
        return -1;
    memset(inconsistencyCheckArr, 0, 9*sizeof(int));
    numberOfUniassignedVar = 0;


    return 0;
}

int arcConsistency(vector<vector<int> >&adjlist, vector<vector<int> >&board) {
    for(int i = 0;i<81;i++) {
        if((adjlist[i].size()==1) && board[i/9][i%9]==0) {
            int suc = prune(adjlist, i/9, i%9, adjlist[i][0], board);
            if(suc==-1)
                return -1;
        }
    }
    return 0;
}

void printsudoku(vector<vector<int> >adjlist){
    cout<<"Answer:"<<endl;
    for(int i=0;i<adjlist.size();i++){
        if(i%9==0){
            cout<<"\n";
        }
        cout<<adjlist[i][0]<<" ";
    }
    cout<<"\n";
}
int solvesudoku(vector<vector<int> >adjlist,int row, int column, int choice, vector<vector<int> >&ans, vector<vector<int> >board){
    if(prune(adjlist,row,column,choice,board)==-1){
        numberOfBacktrack++;
        return -1;
    }
    bool flag = true;
    while(flag) {
        if(arcConsistency(adjlist, board) == -1) {
            numberOfBacktrack++;
            return -1;
        }

        for(int i = 0;i<81;i++) {
            if((adjlist[i].size()==1) && (board[i/9][i%9]==0)) {
                flag = true;
                break;
            }
        }
        flag = false;
    }


    int index=MRV(adjlist, board);
    if(index==INT_MAX){
        ans=adjlist;
        return 0;
    }
    //Apply lcv
    vector<int> lcvalue;
    lcv(adjlist, index, lcvalue);
    //    for(int i=0;i<adjlist[index].size();i++){
    while(lcvalue.size()!=0){
        int choice=lcvalue.back();
        lcvalue.pop_back();
        prob[choice]++;
        if(solvesudoku(adjlist,index/9,index%9,choice,ans, board)==0){
            return 0;
        }
        prob[choice]--;
    }
    numberOfBacktrack++;
    return -1;
}

int isValidSudoku(vector<vector<int> >adjlist) {
    int checkArr[9] = {0};

    for(int i=0;i<9;i++){
        for(int k=0;k<9;k++){
            checkArr[adjlist[9*i+k][0]-1]=1;
        }
        for(int k=0;k<9;k++){
            if(checkArr[k]==0)
                return -1;
        }
        memset(checkArr, 0, 9*sizeof(int));
    }

    for(int i=0;i<9;i++){
        for(int k=0;k<9;k++){
            checkArr[adjlist[9*k+i][0]-1]=1;
        }
        for(int k=0;k<9;k++){
            if(checkArr[k]==0)
                return -1;
        }
        memset(checkArr, 0, 9*sizeof(int));
    }

    // remove from box elements
    for(int i=0;i<9;i++) {
        int subboardi=i/3;
        int subboardj=i%3;
        for(int m=subboardi*3;m<subboardi*3+3;m++){
            for(int n=subboardj*3;n<subboardj*3+3;n++){
                checkArr[adjlist[9*m+n][0]-1] = 1;
            }
        }
        for(int k=0;k<9;k++){
            if(checkArr[k]==0)
                return -1;
        }
        memset(checkArr, 0, 9*sizeof(int));

    }
    return 0;
}


int main(int argc, char *argv[])
{

    int no_test_case;
    std::string input;
    cin >> no_test_case;
    std::getline (std::cin,input);
    while(no_test_case>0)
    {
        numberOfBacktrack = 0;
        for(int k=0;k<9;k++)
            prob[k]=0;

        no_test_case--;
        vector<vector<int> >board(9);
        std::getline (std::cin,input);
        int count=0;
        char temp = input[0];
        if(temp == '\0')
            count += 2;

        for(int i=0;i<9;i++){

            for(int j=0;j<9;j++){
                temp = input[count];
                count=count+2;
                int input1=temp-48;
                // cin>>input;
                board[i].push_back(input1);
                prob[input1]++;
            }

        }
        vector<vector<int> >adjlist(81);
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]!=0){

                    adjlist[9*i+j].push_back(board[i][j]);
                }else{

                    for(int k=1;k<=9;k++){
                        adjlist[9*i+j].push_back(k);
                    }

                }
            }
        }


        high_resolution_clock::time_point t1 = high_resolution_clock::now();


        //preprocess
        for(int i=0;i<adjlist.size();i++){
            if(adjlist[i].size()==1){
                int row=i/9;
                int column=i%9;
                int key=adjlist[i][0];
                //remove from  row elements
                for(int k=0;k<9;k++){
                    if(k!=column){
                        if(find(adjlist[9*row+k].begin(),adjlist[9*row+k].end(),key)!=adjlist[9*row+k].end()){
                            adjlist[9*row+k].erase(std::remove(adjlist[9*row+k].begin(), adjlist[9*row+k].end(), key), adjlist[9*row+k].end());
                        }
                    }
                }
                // remove from column elements
                for(int k=0;k<9;k++){
                    if(k!=row){
                        if(find(adjlist[9*k+column].begin(),adjlist[9*k+column].end(),key)!=adjlist[9*k+column].end()){
                            adjlist[9*k+column].erase(std::remove(adjlist[9*k+column].begin(), adjlist[9*k+column].end(), key), adjlist[9*k+column].end());
                        }
                    }
                }
                // remove from box elements
                int subboardi=row/3;
                int subboardj=column/3;
                for(int m=subboardi*3;m<subboardi*3+3;m++){
                    for(int n=subboardj*3;n<subboardj*3+3;n++){
                        if(m!=row && n!=column){
                            if(find(adjlist[9*m+n].begin(),adjlist[9*m+n].end(),key)!=adjlist[9*m+n].end()){
                                adjlist[9*m+n].erase(std::remove(adjlist[9*m+n].begin(), adjlist[9*m+n].end(), key), adjlist[9*m+n].end());
                            }
                        }
                    }
                }
            }
        }

        if(arcConsistency(adjlist, board)==-1)
            return -1;

        high_resolution_clock::time_point t3 = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>( t3 - t1 ).count();

        //        std::cout << duration<<endl;


        vector<vector<int> >ans(9,vector<int>(1));
        int index=MRV(adjlist, board);

        //Apply lcv
        vector<int> lcvalue;
        lcv(adjlist, index, lcvalue);
        bool resultFound = false;
        //    for(int i=0;i<adjlist[index].size();i++){
        while(lcvalue.size()!=0){
            int choice = lcvalue.back();
            lcvalue.pop_back();
            prob[choice]++;
            if(solvesudoku(adjlist,index/9,index%9,choice,ans, board)==0){
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                duration = duration_cast<microseconds>( t2 - t3 ).count();

                printsudoku(ans);
                resultFound = true;

                std::cout << "*******Time       :- "<<duration<<endl;
                std::cout << "*******Backtracks :- "<<numberOfBacktrack<<endl;


                int success = isValidSudoku(ans);
                if(success == 0)
                    cout << "***************Valid sudoku************"<<endl;
                else
                    cout<<"*************ERROR invalid sudoku*************"<<endl;


                //           return success;
                break;
            }
            prob[choice]--;
        }
        if(!resultFound)
            cout<<"No answer"<<endl;
    }

    return 0;
}

//int lcv(vector<vector<int> >adjlist, int index, vector<int> &lcVal) {
//    int tempArr[9]={0}, choice[9]={0};
//    for(int i=0;i<adjlist[index].size();i++){
//        int key = adjlist[index][i];
//        //        lcValMap.insert(std::pair<int,int>(prob[key],key));

//        int insertLoc = i;
//        //insertion sort
//        for(int j = i-1; j>=0 ; j--) {
//            if(tempArr[j]<prob[key]) {
//                tempArr[j+1] = tempArr[j];
//                choice[j+1] = choice[j];
//                insertLoc = j;
//            }else
//                break;
//        }
//        tempArr[insertLoc] = prob[key];
//        choice[insertLoc] = key;
//    }
//    int j=0;
//    while(j<9 && choice[j]!=0){
//        lcVal.push_back(choice[j]);
//        j++;
//    }
//}


int lcv(vector<vector<int> >adjlist, int index, vector<int> &lcVal) {
    int row = index/9;
    int column = index%9;

    int tempArr[9]={0}, choice[9]={0};
    for(int i=0;i<adjlist[index].size();i++){
        int key = adjlist[index][i];


        int count=0;
        for(int k=0;k<9;k++){
            if(k!=column){
                if(find(adjlist[9*row+k].begin(),adjlist[9*row+k].end(),key)!=adjlist[9*row+k].end()){
                    count++;
                }
            }
        }
        for(int k=0;k<9;k++){
            if(k!=row){
                if(find(adjlist[9*k+column].begin(),adjlist[9*k+column].end(),key)!=adjlist[9*k+column].end()){
                    count++;
                }
            }
        }
        int subboardi=row/3;
        int subboardj=column/3;
        for(int m=subboardi*3;m<subboardi*3+3;m++){
            for(int n=subboardj*3;n<subboardj*3+3;n++){
                if(m!=row && n!=column){
                    if(find(adjlist[9*m+n].begin(),adjlist[9*m+n].end(),key)!=adjlist[9*m+n].end()){
                        count++;
                    }
                }
            }
        }

        int insertLoc = i;
        //insertion sort
        for(int j = i-1; j>=0 ; j--) {
            if(tempArr[j]<count) {
                tempArr[j+1] = tempArr[j];
                choice[j+1] = choice[j];
                insertLoc = j;
            }else
                break;
        }
        tempArr[insertLoc] = count;
        choice[insertLoc] = key;
    }
    int j=0;
    while(j<9 && choice[j]!=0){
        lcVal.push_back(choice[j]);
        j++;
    }
}
