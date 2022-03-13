#include<iostream>
#include<fstream>  //for filehandling
#include<string.h>  //for string operations
#include<sstream>  //for using stringstream class
#include<conio.h>
#include<cstdlib>  //for srand() and rand()
#include<ctime>  //for time()

using namespace std;

int a[10] = {1,2,3,4,5,6,7,8,9,10};   // array 'a' is a global variable

class quiz{
	
	int sno, i, j, temp, score, opt, count, mark, catMark1, catMark2, catMark3 ;
	string f_sno, f_category, f_ques, f_opA, f_opB, f_opC, f_opD, f_opCorrect, line, ans[11], user_name, correctAns, yourAns;
	char ch;
	
	public:
		
		void mainmenu();		//mainmenu
		void start_game();		//starting game
		void result();			//printing final results
		void store_score();		//to store high score data in another file
		void high_score();		//to view high score
		void instructions();	//to view instructions
		void random();			//to randomize the array "a" for each execution
		
}o;  //"o" is the class object
/*--------------------------------------------------------------------------------------------------------*/
void quiz::mainmenu(){
	
	system("cls");
	
	cout<<"\n\t\t\t\t QUIZ GAME";
	cout<<"\n\t\t\t\t `````````\n";
	cout<<"\n\t\t 1. Start Game";
	cout<<"\n\t\t 2. View High Score";
	cout<<"\n\t\t 3. Instructions";
	cout<<"\n\t\t 4. Exit Game";
	cout<<"\n\n\t\t Your Option  :  "; cin>>opt;
	
	switch(opt){
		case 1:
			o.start_game();
			break;
		case 2:
			o.high_score();
			break;
		case 3:
			o.instructions();
			break;
		case 4:
			break;
		default:
			cout<<"\n\t\t ---Invalid Opiton---";
	}
}
/*--------------------------------------------------------------------------------------------------------*/
void quiz::start_game(){
	
	system("cls");
	ifstream fin;
	fin.open("q_bank.txt", ios::in);
	
	if(!fin)
		cout<<"\n ERROR WHILE OPENING \"q_bank.txt\" FILE!";
	
	if(fin){
		cout<<"\n\n\t Your Name : "; fflush(stdin); getline(cin,user_name);
		cout<<"\n\n\t Hello "<<user_name<<" !";
		cout<<"\n\t Hope you'll be enjoying this game.";
		cout<<"\n\n\t Press any key to start the game...";
		ch = getch();
		
		random();
		i = 0, sno = 1, score = 0, count = 0, catMark1 = 0, catMark2 = 0, catMark3 = 0;
		while(getline(fin,line)){                      //to read line by line from q_bank.txt file using getline()
			stringstream linestream(line);			//to read each word in seperate variable of a line using strigstream
			getline(linestream,f_sno,',');
			getline(linestream,f_category,',');
			getline(linestream,f_ques,',');
			getline(linestream,f_opA,',');
			getline(linestream,f_opB,',');
			getline(linestream,f_opC,',');
			getline(linestream,f_opD,',');
			getline(linestream,f_opCorrect,',');
			
			stringstream ss(f_sno);		//to convert string variable into int variable
			int n;
			ss>>n;
			
			if(a[i] == n){
				system("cls");
				cout<<"\n\n\n\t Category : "<<f_category;
				cout<<"\n\n\t Q.no."<<sno<<" : "<<f_ques;
				cout<<"\n\n\t "<<f_opA;
				cout<<"\n\t "<<f_opB;
				cout<<"\n\t "<<f_opC;
				cout<<"\n\t "<<f_opD;
				cout<<"\n\n\t Your Option  :  "; fflush(stdin); getline(cin,ans[i]);
				
				if(ans[i] == f_opCorrect){          //if entered option is correct
					cout<<"\n\n\t Correct Answer !  You are rewarded with 10 points";
					score += 10;
					count += 1;
					cout<<"\n\t Score = "<<score;
					if(f_category == "Programming")	catMark1 += 10;
					if(f_category == "Information Technology")	catMark2 += 10;
					if(f_category == "General Knowledge")	catMark3 += 10;
				}
				if(ans[i] != f_opCorrect){			//if entered option is wrong
					cout<<"\n\n\t Wrong Answer... You are rewarded with 0 point";
					cout<<"\n\t The correct option is ("<<f_opCorrect<<")";
					score += 0;
					cout<<"\n\t Score = "<<score;
				}
				cout<<"\n\n\t Press any key for next...";
				cout<<"\n\t Press \'q\' to quit the game...";
				ch = getch();
				if(ch == 'q' || ch == 'Q'){
					fin.seekg(0,ios::beg);
					o.mainmenu();
					break;
				}		
				sno ++;
				i ++;
				fin.seekg(0,ios::beg);
			}			
		}
		fin.close();
		o.result();
	}

}
/*--------------------------------------------------------------------------------------------------------*/
void quiz::result(){
	
	system("cls");
	ifstream fin;
	fin.open("q_bank.txt", ios::in);
	
	if(!fin)
		cout<<"\n ERROR WHILE OPENING \"q_bank.txt\" FILE!";
	
	if(fin){
		cout<<"\n\n\t Congratulations "<<user_name<<". You have completed the quiz game.";
		cout<<"\n\t You have got "<<count<<" correct out of 10 questions.";
		cout<<"\n\n\t Here are your answers :-";
		cout<<"\n\t ************************";
		i = 0;
		sno = 1;
		
		while(getline(fin,line)){
			stringstream linestream(line);
			getline(linestream,f_sno,',');
			getline(linestream,f_category,',');
			getline(linestream,f_ques,',');
			getline(linestream,f_opA,',');
			getline(linestream,f_opB,',');
			getline(linestream,f_opC,',');
			getline(linestream,f_opD,',');
			getline(linestream,f_opCorrect,',');
			
			stringstream ss(f_sno);
			int n;
			ss>>n;
			
			if(a[i] == n){
				string x1="a",x2="b",x3="c",x4="d";
				/* for correctAns variable */
				if(f_opCorrect == x1)	correctAns = f_opA;
				if(f_opCorrect == x2)	correctAns = f_opB;
				if(f_opCorrect == x3)	correctAns = f_opC;
				if(f_opCorrect == x4)	correctAns = f_opD;
				/* for yourAns variable */
				if(ans[i] == x1)	yourAns = f_opA;
				if(ans[i] == x2)	yourAns = f_opB;
				if(ans[i] == x3)	yourAns = f_opC;
				if(ans[i] == x4)	yourAns = f_opD;
				
				cout<<"\n\t Category        : "<<f_category;
				cout<<"\n\t Q.no            : "<<sno;
				cout<<"\n\t Question        : "<<f_ques;
				cout<<"\n\t Correct Answer  : "<<correctAns;
				cout<<"\n\t Your Answer     : "<<yourAns;
				if(ans[i] == f_opCorrect) mark = 10;
				else mark = 0;
				cout<<"\n\t Marks Awarded   : "<<mark;
				cout<<"\n\t -------------------------------------------------------------------";
				sno ++;
				i ++;
				fin.seekg(0,ios::beg);
			}
			
		}
		fin.close();
		cout<<"\n\n\t Press any key for next...";
		ch = getch();
		 
		system("cls");

		cout<<"\n\n\t Category Wise Marks :-";
		cout<<"\n\t **********************";
		cout<<"\n\t Programming             :  "<<catMark1;
		cout<<"\n\t Information Technology  :  "<<catMark2;
		cout<<"\n\t General Knowledge       :  "<<catMark3;
		cout<<"\n\n\t Press any key for next...";
		ch = getch();
		
		cout<<"\n\n\t Your Final Total Score  :  "<<score<<" out of 100";
		cout<<"\n\n\t Press any key to go mainmenu...";
		ch = getch();
		o.store_score();  //calling store_score() to store the highest score data
		o.mainmenu();
	}
}
/*--------------------------------------------------------------------------------------------------------*/
void quiz::store_score(){
	ofstream temp;
	temp.open("temp.txt", ios::out);
	ifstream myfile;
	myfile.open("score.txt", ios::in);  //initially score.txt contains [0,name] -> 0-score, name-Name
	if(!temp || !myfile)	
		cout<<"\n\n\t ERROR WHILE OPENING \"score.txt\" OR \"temp.txt\" FILE!";
	if(myfile && temp){
		int totScore;
		char name[25];
		myfile>>totScore>>name;
		
		if(score >= totScore ){
			temp<<score<<","<<user_name;
		}
	}
	myfile.close();
	temp.close();
	remove("score.txt");
	rename("temp.txt","score.txt");
}
/*--------------------------------------------------------------------------------------------------------*/
void quiz::high_score(){
	
	system("cls");
	ifstream fin;
	fin.open("score.txt", ios::in);
	if(!fin)   cout<<"\n\n\t ERROR WHILE OPENING \"score.txt\" FILE!";
	if(fin){
		string totScore, name;
		getline(fin,totScore,',');
		getline(fin,name,',');
		
		cout<<"\n\n";
		cout<<"\n\t  _       _   _   ________    _       _        ________   ________   ________   ________   ________                    ";
		cout<<"\n\t | |     | | | | |  ______|  | |     | |      |  ______| |  ______| |  ____  | |   ___  | |  ______|                   ";
		cout<<"\n\t | |     | | | | | |         | |     | |      | |        | |        | |    | | |  |   | | | |                          ";
		cout<<"\n\t | |_____| | | | | |  _____  | |_____| |      | |______  | |        | |    | | |  |___| | | |______                    ";
		cout<<"\n\t | |_____| | | | | | |___  | | |_____| |      |______  | | |        | |    | | |  __  __| |  ______|                   ";
		cout<<"\n\t | |     | | | | | |     | | | |     | |             | | | |        | |    | | | |  \\ \\   | |                          ";
		cout<<"\n\t | |     | | | | | |_____| | | |     | |       ______| | | |______  | |____| | | |   \\ \\  | |______                    ";
		cout<<"\n\t |_|     |_| |_| |_________| |_|     |_|      |________| |________| |________| |_|    \\_\\ |________|                   ";
		
		
		cout<<"\n\n\n\t Name   :  "<<name;
		cout<<"\n\t Score  :  "<<totScore;
	}
	fin.close();
	cout<<"\n\n\t Press any key to go mainmenu...";
	ch = getch();
	o.mainmenu();
}
/*--------------------------------------------------------------------------------------------------------*/
void quiz::instructions(){
	
	system("cls");
	
	cout<<"\n\n\t\t\t\t WELCOME TO QUIZ GAME";
	cout<<"\n\t\t\t\t ********************";
	cout<<"\n\n\t NOTE: Please note these instrucions before you start to play.";
	cout<<"\n\n\t 1. You will be given with 10 questions to complete this quiz game";
	cout<<"\n\t 2. Each question has 10 points";
	cout<<"\n\t 3. Each question is based on 3 different categories";
	cout<<"\n\t 4. Enter the option letter to answer the question [ Eg: a (or) c ]";
	cout<<"\n\t 5. The option letters you enter are case sensitive (only lowercase)";
	cout<<"\n\t 6. Your final results will be displayed in the end";
	cout<<"\n\n";
	
	cout<<"\n\t                       **                                                          ";
	cout<<"\n\t *      ****** ******* **  ******       ****** *******   **   ******  *******      ";
	cout<<"\n\t *      *         *    *  *            *          *    *    * *     *    *         ";
	cout<<"\n\t *      ******    *        ******       ******    *    ****** ******     *         ";
	cout<<"\n\t *      *         *              *            *   *    *    * *    *     *         ";
	cout<<"\n\t ****** ******    *        ******       ******    *    *    * *     *    *         ";
	
	cout<<"\n\n\t Press any key to go mainmenu...";
	if(ch=getch())
		o.mainmenu();
	
}
/*--------------------------------------------------------------------------------------------------------*/
void quiz::random(){
	srand(time(0));
	for(i = 0; i<10; i++){
		j = (rand()%9) + 1;
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	//a[] contains 1 to 10 in random order
}
/*--------------------------------------------------------------------------------------------------------*/
int main(){
	system("cls");
	o.mainmenu();
	cout<<"\n\n---------------------------------\n";
	system("pause");
	return 0;
}
