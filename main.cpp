// 10627130 資工二甲 林冠良 & 10627131 資工二甲 李峻瑋 // CodeBlocks 17.12
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

#define SWAP(x,y) {int t; t = x; x = y; y = t;}

using namespace std ;

static ifstream input ;
static ofstream output ;
static int QueueTime1 = 0 ;
static int QueueTime2 = 0 ;
static int FileN = 0 ;

typedef struct OrderStuct {
    int id = 0 ;
    int arrivalTime = 0 ;
    int duration = 0 ;
    int timeout = 0 ;
    int delay = 0 ;
    string whole = "\0" ;
} Data ;

class Functions {

    vector<OrderStuct> orders ;
    string labels = "\0" ;

public:

    void shellSort() {
        int dataCount = 0 ;
        string sentence = "\0" ;
        OrderStuct tempOrder ;
        orders.clear() ;
        getline( input, labels ) ; // get the labels

        while ( getline( input, sentence ) ) {
            tempOrder.whole = sentence ; // save the whole data first
            vector<string> data ;
            string token ;
            istringstream cut( sentence ) ;
            while ( getline( cut, token, '\t' ) ) data.push_back( token ) ; // cut the data
            tempOrder.id = atoi( data[0].c_str() ) ; // set the first token to id
            tempOrder.arrivalTime = atoi( data[1].c_str() ) ; // set the second token to arrivalTime
            tempOrder.duration = atoi( data[2].c_str() ) ; // set the third token to duration
            tempOrder.timeout = atoi( data[3].c_str() ) ; // set the forth token to timeout
            orders.push_back( tempOrder ) ; // push tempOrder to the orders dataBase
            dataCount++ ;
        } // read and analyze the data

        OrderStuct temp ;
        for( int gap = dataCount/2 ; gap > 0 ; gap /= 2 ) {
            for( int i = gap ; i < dataCount ; i += 1 ) {
                temp = orders[i] ;
                int j ;
                for ( j = i ; j >= gap && orders[j-gap].arrivalTime > temp.arrivalTime ; j -= gap ) orders[j] = orders[j-gap] ;
                orders[j] = temp ;
            } // for()
        } // for()

        for ( int i = 0 ; i < orders.size() ; i ++ ) {
            if ( orders[i].arrivalTime == orders[i+1].arrivalTime && orders[i].id > orders[i+1].id ) swap( orders[i], orders[i+1] ) ;
        } // for()
        for ( int i = 0 ; i < orders.size() ; i ++ ) {
            if ( orders[i].arrivalTime == orders[i+1].arrivalTime && orders[i].id > orders[i+1].id ) swap( orders[i], orders[i+1] ) ;
        } // for()
        for ( int i = 0 ; i < orders.size() ; i ++ ) {
            if ( orders[i].arrivalTime == orders[i+1].arrivalTime && orders[i].id > orders[i+1].id ) swap( orders[i], orders[i+1] ) ;
        } // for()

        if ( FileN == 401 ) output.open( "sort401.txt" ) ;
        else if ( FileN == 402 ) output.open( "sort402.txt" ) ;

        output << labels << endl ;
        for( int i = 0 ; i < orders.size() ; i ++ ) output << orders[i].whole << endl ;
    } // shellSort()

} ;

int main() {

    int command = 0 ;
    bool continueOrNot = false ;
    Functions shellSort ;
    Functions simulate ;
    Functions doubleSimulate ;

    do {
        cout << "*****************************************" << endl ; // welcome message
        cout << "***    Simulate FIFO Queues by SQF    ***" << endl ;
        cout << "*** 0 : Quit                          ***" << endl ;
        cout << "*** 1 : Sort a file                   ***" << endl ;
        cout << "*** 2 : Simulate one FIFO queue       ***" << endl ;
        cout << "*** 3 : Simulate two queues by SQF    ***" << endl ;
        cout << "*****************************************" << endl ;
        cout << endl << "Please enter your choice :" << endl ;

        cin >> command ; // read in user command

        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit

        else if ( command > 3 || command < 0 ) {
            cout << "Error command! please enter an acceptable command :" << endl << endl ;
            continueOrNot = true ;
        } // wrong command

        else if ( command == 1 ) {

            bool function1Confirm = false ;

            do {
                cout << "Please enter the file you want to sort or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == 0 ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else if ( FileN != 401 && FileN != 402  )
                    cout << "*****  input" << FileN << ".txt does not exist!  *****" << endl ;

                else if ( FileN == 401 ) {
                    input.open( "input401.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  input401.txt does not exist!  *****" << endl ;

                    else {
                        function1Confirm = true ;
                        simulate.shellSort() ;
                        continueOrNot = true ;
                    } // find input 401
                } // test if you have already create a sort file

                else if ( FileN == 402 ) {
                    input.open( "input402.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  input402.txt does not exist!  *****" << endl ;

                    else {
                        function1Confirm = true ;
                        simulate.shellSort() ;
                        continueOrNot = true ;
                    } // find input 402
                } // test if you have already create a sort file

            } while ( ! function1Confirm ) ;

            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 2

        else if ( command == 2 ) {

            bool function2Confirm = false ;

            do {
                cout << "Please enter the file you want to simulate or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == 0 ) {
                    function2Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else if ( FileN != 401 && FileN != 402  )
                    cout << "*****  sort" << FileN << ".txt does not exist!  *****" << endl ;

                else if ( FileN == 401 ) {
                    input.open( "sort401.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  sort401.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                    } // find sort 401
                } // test if you have already create a sort file

                else if ( FileN == 402 ) {
                    input.open( "sort402.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  sort402.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                    } // find sort 402
                } // test if you have already create a sort file

            } while ( ! function2Confirm ) ;

            FileN = 0 ;
            input.close() ;
            output.close() ;

        } // mission 2

        else if ( command == 3 ) {

            bool function3Confirm = false ;

            do {
                cout << "Please enter the file you want to simulate or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == 0 ) {
                    function3Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else if ( FileN != 401 && FileN != 402  )
                    cout << "*****  sort" << FileN << ".txt does not exist!  *****" << endl ;

                else if ( FileN == 401 ) {
                    input.open( "sort401.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  sort401.txt does not exist!  *****" << endl ;

                    else {
                        function3Confirm = true ;
                        continueOrNot = true ;
                    } // find sort 401
                } // test if you have already create a sort file

                else if ( FileN == 402 ) {
                    input.open( "sort402.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  sort402.txt does not exist!  *****" << endl ;

                    else {
                        function3Confirm = true ;
                        continueOrNot = true ;
                    } // find sort 402
                } // test if you have already create a sort file

            } while ( ! function3Confirm ) ;

            FileN = 0 ;
            input.close() ;
            output.close() ;

        } // mission 3

    } while( continueOrNot ) ;
} // main()
