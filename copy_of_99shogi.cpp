#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <random>
#include <time.h>

using namespace std;

enum {
	emp,
	sfu,
	sky,
	ske,
	sgi,
	ski,
	ska,
	shi,
	sto,
	sny,
	snk,
	sng,
	sum,
	sry,
	sgy,
	efu = -1,
	eky = -2,
	eke = -3,
	egi = -4,
	eki = -5,
	eka = -6,
	ehi = -7,
	eto = -8,
	eny = -9,
	enk = -10,
	eng = -11,
	eum = -12,
	ery = -13,
	egy = -14,
};

string FU = "FU";
string KY = "KY";
string KE = "KE";
string GI = "GI";
string KI = "KI";
string KA = "KA";
string HI = "HI";
string TO = "TO";
string NY = "NY";
string NK = "NK";
string NG = "NG";
string UM = "UM";
string RY = "RY";
string GY = "GY";

#define board(a) (_board+(a)*9)

int _board[81] = {
	eky, eke, egi, eki, egy, eki, egi, eke, eky,
	emp, ehi, emp, emp, emp, emp, emp, eka, emp,
	efu, efu, efu, efu, efu, efu, efu, efu, efu,
	emp, emp, emp, emp, emp, emp, emp, emp, emp,
	emp, emp, emp, emp, emp, emp, emp, emp, emp,
	emp, emp, emp, emp, emp, emp, emp, emp, emp,
	sfu, sfu, sfu, sfu, sfu, sfu, sfu, sfu, sfu,
	emp, ska, emp, emp, emp, emp, emp, shi, emp,
	sky, ske, sgi, ski, sgy, ski, sgi, ske, sky,
};

string te[100];
string ete[100];
string new_ete[100];
string komate[560];
string ekomate[560];

int a;
int b;
int c;
int d;
int e;
int f;
int ff;
int x;
int r;
int mr;
int mnr;
int nx;
string sKoma[40];

string eKoma[40];
string koma;
string tt;
string buffer;
string buff;



int fusion();

void draw() {
	cout<<endl<<" 9  8  7  6  5  4  3  2  1 "<<endl;
	int v;
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if((v=board(i)[j])==0){
				cout<<" * ";
			}else{
				cout<<(v<0?"-":"+");
				switch(abs(v)) {
					case sfu: cout<<"歩"; break;
					case sky: cout<<"香"; break;
					case ske: cout<<"桂"; break;
					case sgi: cout<<"銀"; break;
					case ski: cout<<"金"; break;
					case ska: cout<<"角"; break;
					case shi: cout<<"飛"; break;
					case sto: cout<<"と"; break;
					case sny: cout<<"杏"; break;
					case snk: cout<<"圭"; break;
					case sng: cout<<"全"; break;
					case sum: cout<<"馬"; break;
					case sry: cout<<"竜"; break;
					case sgy: cout<<"玉"; break;
					default: break;
				}
			}
		}
		cout<<" "<<i+1<<endl<<endl;
	}
}

int komaBoard(string koma) {
	if(koma == "FU") {
		//cout<<"eureka"<<endl;
		return sfu;
	}else if(koma == "KY") {
		return sky;
	}else if(koma == "KE") {
		return ske;
	}else if(koma == "GI") {
		return sgi;
	}else if(koma == "KI") {
		return ski;
	}else if(koma == "KA") {
		return ska;
	}else if(koma == "HI") {
		return shi;
	}else if(koma == "TO") {
		return sfu;
	}else if(koma == "NY") {
		return sny;
	}else if(koma == "NK") {
		return snk;
	}else if(koma == "NG") {
		return sgi;
	}else if(koma == "UM") {
		return ska;
	}else if(koma == "RY") {
		return shi;
	}else if(koma == "GY") {
		return sgy;
	}
	return 0;
}

#define komaOp(koma) (-komaBoard(koma))

string nariKind(string koma) {
	if(koma == "FU") {
		return "TO";
	}else if(koma == "KY") {
		return "NY";
	}else if(koma == "KE") {
		return "NK";
	}else if(koma == "GI") {
		return "NG";
	}else if(koma == "KA") {
		return "UM";
	}else if(koma == "HI") {
		return "RY";
	}
	return 0;
}


string komaKind(int i, int j) {
	switch(abs(board(i)[j])) {
		case sfu:return FU;
		case sky:return KY;
		case ske:return KE;
		case sgi:return GI;
		case ski:return KI;
		case ska:return KA;
		case shi:return HI;
		case sto:return TO;
		case sng:return NG;
		case sum:return UM;
		case sry:return RY;
		case sgy:return GY;
	}
	return 0;
}

void keTobi(int i, int j, int s) {
	if(board(i)[j] > 0) {
		if(i-2 >= 0) {
			flag = 0;
			if(j-1 >= 0) {
				if(board(i-2)[j-1] != 0) {
							flag++;
				}
				if(board(i-2)[j-1] > 0) {
							flag++;
				}
				for(int n = 0; n < 100; n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j-1) + i-2) + komaKind(i, j);
						break;
					}
				}
			}
			flag = 0;
			if(j+1 <= 9) {
				if(board(i-2)[j+1] != 0) {
							flag++;
				}
				if(board(i-2)[j+1] > 0) {
							flag++;
				}
				for(int n = 0; n < 100; n++) {
					if(te[n].empty() != 0 && flag < 2) {
						te[n] = to_string(1000 * j + 100 * i + 10 * (j+1) + i-2) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
	
	if(board(i)[j] < 0) {
		if(i+2 <= 9) {
			flag = 0;
			if(j-1 >= 0) {
				if(board(i+2)[j-1] != 0) {
							flag++;
				}
				if(board(i+2)[j-1] < 0) {
							flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(ete[n].empty() != 0 && flag < 2) {
						ete[n] = to_string(1000 * j + 100 * i + 10 * (j-1) + i+2) + komaKind(i, j);
						break;
					}
				}
			}
			flag = 0;
			if(j+1 <= 9) {
				if(board(i+2)[j+1] != 0) {
							flag++;
				}
				if(board(i+2)[j+1] < 0) {
							flag++;
				}
				for(int n = 0; n < sizeof(te[100]); n++) {
					if(ete[n].empty() != 0 && flag < 2) {
						ete[n] = to_string(1000 * j + 100 * i + 10 * (j+1) + i+2) + komaKind(i, j);
						break;
					}
				}
			}
		}
	}
}

#define moveto_sub(ud,t) \
do{\
	for(int k = 1; k <= s; k++) {\
		if((ud == -1 ? i-k >= 0 : ud == 1 ? i+k <= 9 ? true) &&\
		   (rl == -1 ? j-k >= 0 : rl == 1 ? j+k <= 9 ? true) && board(i+k*ud)[j+k*rl]) {\
			for(int n = 0; n < 100; n++) {\
				if(t[n].empty()) {\
					t[n] = to_string(1000 * j + 100 * i + 10 * (j+k*rl) + i+k*ud) + komaKind(i, j);\
					break;\
				}\
			}\
			if(board(i+k*ud)[j+k*rl]) break;\
		}else break;\
	}\
}while(false)

#define moveto(ud,rl) \
do{\
	if(board(i)[j] > 0) {\
		moveto_sub(-1*ud, rl, te);\
	} else if(board(i)[j] < 0) {\
		moveto_sub(ud, rl, ete);\
	}\
}while(false)

void above (int i, int j, int s) { moveto( 1,  0); }
void below (int i, int j, int s) { moveto(-1,  0); }
void right (int i, int j, int s) { moveto( 0,  1); }
void left  (int i, int j, int s) { moveto( 0, -1); }
void UeNaMi(int i, int j, int s) { moveto( 1,  1); }
void SiNaMi(int i, int j, int s) { moveto(-1,  1); }
void UeNaHi(int i, int j, int s) { moveto( 1, -1); }
void SiNaHi(int i, int j, int s) { moveto(-1, -1); }

//!
void seiri() {
	for(int i = 0; i < 100; i++) {
		if(!te[i].empty()) {
			while(te[i].size() != 6) {
				te[i] = "0" + te[i];
			}
		}
		if(!ete[i].empty()) {
			while(ete[i].size() != 6) {
				ete[i] = "0" + ete[i];
			}
		}
	}
}

void ekoma(int i, int j) {
	int kf = 0;
	int ki = 0;

	if(board(i)[j] != 0) {
		while(kf == 0) {
			if(eKoma[ki].empty() != 0) {
				eKoma[ki] = komaKind(i, j);
				kf++;
			}
			ki++;
			if(ki > 40) {
				kf++;
			}
		}
	}else {
		return;
	}
}

void op() {
	int kf = 0;
	int ki = 0;
	int i = 0;
	int j = 0;
	cout<<"Black >";
	cin>>tt;

	x = stoi(tt.substr(0, 4));
	koma = tt.substr(4, 5);

	/*a = x / 1000;
	b = (x % 1000) /100;
	c = (x % 100) / 10;
	d = x % 10;*/

	e = 0;
	f = 0;
	//b -= 1;
	//d -= 1;

	if(tt.substr(0, 1) != "0" && tt.substr(1, 2) != "0") {
		a = x / 1000;
		b = (x % 1000) /100;
		c = (x % 100) / 10;
		d = x % 10;
		
		b -= 1;
		d -= 1;
		while(f == 0) {
			if((a + e) == 9) {
				a = e;
				f++;
			}
			e++;
		}
		e = 0;
		f = 0;
		while(f == 0) {
			if((c + e) == 9) {
				c = e;
				f++;
			}
			e++;
		}
		i = d;
		j = c;
		ekoma(i, j);
		
		board(d)[c] = komaOp(koma);
		board(b)[a] = 0;
	}else {
		a = x / 1000;
		b = (x % 1000) /100;
		c = (x % 100) / 10;
		d = x % 10;
		
		b -= 1;
		d -= 1;
		
		e = 0;
		f = 0;
		while(f == 0) {
			if((c + e) == 9) {
				c = e;
				f++;
			}
			e++;
		}
		
		i = d;
		j = c;
		ekoma(i, j);
		
		board(d)[c] = komaOp(koma);
	}

	/*i = d;
	j = c;

	ekoma(i, j);

	if(a == 9 && c == 9) {
		board(d)[c] = komaOp(koma);
	}else {

		board(d)[c] = komaOp(koma);
		board(b)[a] = 0;
	}*/
}

void eval() {

}

void skoma(int i, int j) {
	int kf = 0;
	int ki = 0;

	if(board(i)[j] != 0) {
		while(kf == 0) {
			if(sKoma[ki].empty() != 0) {
				sKoma[ki] = komaKind(i, j);
				kf++;
			}
			ki++;
			if(ki > 40) {
				kf++;
			}
		}
	}else {
		return;
	}
}

/*void naru() {
	int naruI = 0;
	for(int i = 0; i < 100; i++) {
		int naruI = 0;
		while(naruI == 0) {
			if((stoi(te[i].substr(2, 3))) <= 2 && (komaBoard(te[i].substr(4, 5)))) {
				for(int j = 0; j < 100; j++) {
					if(te[j].empty() != 0) {
						koma = te[i].substr(4, 5);
						te[j] = te[i].substr(0, 4) + nariKind(koma);
						naruI++;
					}
					if(j == 100) {
						naruI++;
					}
				}
			}
		}
	}
}*/

int enaru() {
	//istringstream oneone;
	//istringstream threeone;
	for(int i = 0; i < 100; i++) {
		cout<<endl<<ete[i]<<" "<<ete[i].substr(1, 1)<<" "<<ete[i].substr(3, 1);
		//oneone = istringstream(ete[i].substr(1, 1));
		//threeone = istringstream(ete[i].substr(3, 1));
		if(stoi(ete[i].substr(1, 1)) < 7 && stoi(ete[i].substr(3, 1)) >= 7) {
			cout<<"done"<<endl;
			for(int j = 0; j < 100; j++) {
				if(ete[j].empty() != 0) {
					koma = ete[i].substr(3, 1);
					ete[j] = ete[i].substr(0, 4) + nariKind(koma);
					
				}
					
			}
		}

	}
	return 0;
}

void sop() {
	//string te[100];
	int fl = 0;
	int kf = 0;
	int ki = 0;
	int i = 0;
	int j = 0;
	int kff = 0;

	eval();

	srand(time(NULL));
	//int ir = rand() % 100 + 0;
	while(fl == 0) {

		r = rand() % 660 + 0;

		//cout<<r<<endl;

		if(te[r].empty() == 0 || komate[r-100].empty() == 0) {
			if(r <= 100) {
				x = stoi(te[r].substr(0, 4));
				koma = te[r].substr(4, 5);

				a = x / 1000;
				b = (x % 1000) /100;
				c = (x % 100) / 10;
				d = x % 10;

				i = d;
				j = c;

				skoma(i, j);

				/*if(a == 0) {
					for(int u = 0; u < 9; u++) { //5
					if(board(u)[j] == sfu) {
							kff++;
					}
				}
				if(j == 0) {
					kff++;
				}
				if(kff == 0) {
					board(i)[j] = komaBoard(koma);
					cout<<endl<<"White >"<<te[r]<<endl;
				}
				break;
				}*/
				string moKoma = te[r].erase(0, 4);

				cout<<endl<<"White >"<<9-a<<b+1<<9-c<<d+1<<moKoma<<endl;
				board(d)[c] = board(b)[a];
				board(b)[a] = 0;
				
				//wc++;
				fl++;
			}else if(komate[r-100].empty() == 0){
				r -= 100;
				x = stoi(komate[r].substr(0, 4));
				koma = komate[r].substr(4, 5);

				a = x / 1000;
				b = (x % 1000) /100;
				c = (x % 100) / 10;
				d = x % 10;

				i = d;
				j = c;

				skoma(i, j);

				/*if(a == 0) {
					for(int u = 0; u < 9; u++) { //5
						if(board(u)[j] == sfu) {
							kff++;
						}
					}
					if(j == 0) {
						kff++;
					}
					if(kff == 0) {
						board(i)[j] = komaBoard(koma);
						cout<<endl<<"White >"<<te[r]<<endl;
					}
					break;
				}*/
				string moKoma = komate[r].erase(0, 4);
	
				cout<<endl<<"White >"<<"M"<<"+"<<9-c<<d+1<<moKoma<<endl;
				if(moKoma == "FU") { // or while
					for(int i = 0; i < 40; i++) {
						if(sKoma[i] == "FU") {
							sKoma[i] = "";
							break;
						}
					}
					board(d)[c] = sfu;
				}
				if(moKoma == "KI") {
					for(int i = 0; i < 40; i++) {
						if(sKoma[i] == "KI") {
							sKoma[i] = "";
							break;
						}
					}
					board(d)[c] = ski;
				}			
			
				//wc++;
				fl++;
			}
			
		}

	}
	//te[100] = {};

}

void gameRule() {
	int i = 0;
	int j = 0;
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			switch(abs(board(i)[j])) {
				case sfu:
					above (i, j, 1); break;
				case sky:
					above (i, j, 9); break;
				case ske:
					keTobi(i, j, 1); break;
				case sgi:
					above (i, j, 1);
					UeNaMi(i, j, 1);
					UeNaHi(i, j, 1);
					SiNaMi(i, j, 1);
					SiNaHi(i, j, 1); break;
				case sto:
				case sny:
				case snk:
				case sng:
				case ski:
					above (i, j, 1);
					below (i, j, 1);
					UeNaMi(i, j, 1);
					UeNaHi(i, j, 1);
					right (i, j, 1);
					left  (i, j, 1); break;
				case ska:
					UeNaMi(i, j, 9);
					UeNaHi(i, j, 9);
					SiNaMi(i, j, 9);
					SiNaHi(i, j, 9); break;
				case shi:
					above (i, j, 9);
					below (i, j, 9);
					right (i, j, 9);
					left  (i, j, 9); break;
				case sum:
					above (i, j, 1);
					below (i, j, 1);
					right (i, j, 1);
					left  (i, j, 1);
					UeNaMi(i, j, 9);
					UeNaHi(i, j, 9);
					SiNaMi(i, j, 9);
					SiNaHi(i, j, 9); break;
				case sry:
					UeNaMi(i, j, 1);
					UeNaHi(i, j, 1);
					SiNaMi(i, j, 1);
					SiNaHi(i, j, 1);
					above (i, j, 9);
					below (i, j, 9);
					right (i, j, 9);
					left  (i, j, 9); break;
				case sgy:
					above (i, j, 1);
					below (i, j, 1);
					right (i, j, 1);
					left  (i, j, 1);
					UeNaMi(i, j, 1);
					UeNaHi(i, j, 1);
					SiNaMi(i, j, 1);
					SiNaHi(i, j, 1); break;
				default: break;
			}
			/*
			for(int n = 0; i < 10; n++) {
				if(eKoma[n].empty() == 0) {
					if(board(i)[j] == 0) {
						for(int p = 0; n < 100; p++) {
							if(te[p].empty() != 0) {
								te[p] = to_string(9000 + 900 + 10 * j + i) + eKoma[n];

							}
						}
					}
				}
			}*/

		}
	}

	seiri();
}

int koma_check;
int koma_check_j;
int koma_check_do;
int koma_check_num;
int koma_check_count;
int ekoma_check;
int ekoma_check_j;
int ekoma_check_do;
int ekoma_check_num;
int ekoma_check_count;

/*for(int i = 0; i < 40; i++) {
	if(sKoma[i].empty() == 0) {
		koma_check_kount++;
	}
}

string tsumeSkoma[koma_check_kount];*/
void Koma() {
	int tsumeSkomaJ = 0;
	int koma_check_kount = 0;
	/*string tsumeSkoma[koma_check_kount];*/
	for(int i = 0; i < 40; i++) {
		if(sKoma[i].empty() == 0) {
			koma_check_kount++;
		}
	}
	string tsumeSkoma[tsumeSkomaJ];
	//string tsumeSkoma[koma_check_kount];
	for(int i = 0; i < 40; i++) {
		if(sKoma[i].length() > 0) {
			tsumeSkoma[tsumeSkomaJ] = sKoma[i];
			tsumeSkomaJ++;
		}
	}
	
	for(int i = 0; i < 40; i++) {
		sKoma[i] = "";
	}
	for(int i = 0; i < koma_check_kount; i++) {
		//cout<<temp[i]<<endl;
		sKoma[i] = tsumeSkoma[i];
	}

	int kc = 0;
	for(int n = 0; n < 40; n++) {
		if(sKoma[n].empty() == 0) {
			flag = 0;
			kc = 0;
			for(int i = 0; i < 9; i++) {
				for(int j = 0; j < 9; j++) {
					if(board(i)[j] == 0) {
						flag = 0;
						while(flag == 0) {
							if(komate[kc].empty() != 0) {
								for(int u = 0; u < 560; u++) {
									if(komate[u] == to_string(9000 + 10 * j + i) + sKoma[n]) {
										komate[u] = "";
									}
								}
								komate[kc] = to_string(9000 + 10 * j + i) + sKoma[n];
								flag++; 
							}
							if(kc > 560) {
								flag++;
							}
							kc++;
						}
					}
				}
			}
		}
	}
}

void ekoma() {
	int etsumeSkomaJ = 0;
	int ekoma_check_kount = 0;
	/*string tsumeSkoma[koma_check_kount];*/
	for(int i = 0; i < 40; i++) {
		if(eKoma[i].empty() == 0) {
			ekoma_check_kount++;
		}
	}
	string etsumeSkoma[etsumeSkomaJ];
	//string tsumeSkoma[koma_check_kount];
	for(int i = 0; i < 40; i++) {
		if(eKoma[i].length() > 0) {
			etsumeSkoma[etsumeSkomaJ] = eKoma[i];
			etsumeSkomaJ++;
		}
	}
	
	for(int i = 0; i < 40; i++) {
		eKoma[i] = "";
	}
	for(int i = 0; i < ekoma_check_kount; i++) {
		//cout<<temp[i]<<endl;
		eKoma[i] = etsumeSkoma[i];
	}

	int kc = 0;
	for(int n = 0; n < 40; n++) {
		if(eKoma[n].empty() == 0) {
			flag = 0;
			kc = 0;
			for(int i = 0; i < 9; i++) {
				for(int j = 0; j < 9; j++) {
					if(board(i)[j] == 0) {
						flag = 0;
						while(flag == 0) {
							if(ekomate[kc].empty() != 0) {
								for(int u = 0; u < 560; u++) {
									if(ekomate[u] == to_string(9000 + 10 * j + i) + eKoma[n]) {
										ekomate[u] = "";
									}
								}
								ekomate[kc] = to_string(9000 + 10 * j + i) + eKoma[n];
								flag++; 
							}
							if(kc > 560) {
								flag++;
							}
							kc++;
						}
					}
				}
			}
		}
	}
}

int fusion() {
	x = (1000 * a) + (100 * b) + (10 * c) + d;

	return x;
}

/*string getHCR() {
	f = 0;
	x = stoi(te[r].substr(0, 4));
	koma = te[r].substr(4, 5);

	a = x / 1000;
	b = (x % 1000) /100;
	c = (x % 100) / 10;
	d = x % 10;

	e = 0;
	f = 0;
	b -= 1;
	d -= 1;
	while(f == 0) {
		if((a + e) == 5) {
			a = e;
			f++;
		}
		e++;
	}
	e = 0;
	f = 0;
	while(f == 0) {
		if((c + e) == 5) {
			c = e;
			f++;
		}
		e++;
	}

	x = (1000 * a) + (100 * b) + (10 * c) + d;

	te[r] = to_string(x) + koma;

	if(te[r].empty() == 0) {
		while(te[r].size() != 6) {
			te[r] = "0" + te[r];
		}
	}

	buff = te[r];
	return buff;
}*/

void nifu() {
	for(int i = 0; i < 560; i++) {
		if(komate[i].empty() == 0) {
			//cout<<"ok\n";
			x = stoi(komate[i].substr(0, 4));
			koma = komate[i].substr(4, 5);

			a = x / 1000;
			b = (x % 1000) /100;
			c = (x % 100) / 10;
			d = x % 10;

			if(9-a == 0) {
				//cout<<"ok\n";
				for(int j = 0; j < 9; j++) {
					if(board(j)[c] == sfu && koma == "FU") {
						komate[i] = "";
					}
				}
			}
		}
	}
	for(int i = 0; i < 560; i++) {
		if(komate[i].empty() == 0) {
			koma_check_num++;
		}
	}
	string tsumekoma[koma_check_num];
	int tsumekomaJ = 0;
	for(int i = 0; i < 560; i++) {
		if(komate[i].length() > 0) {
			tsumekoma[tsumekomaJ] = komate[i];
			tsumekomaJ++;
		}
	}
	for(int i = 0; i < 560; i++) {
		komate[i] = "";
	}
	for(int i = 0; i < koma_check_num; i++) {
		//cout<<temp[i]<<endl;
		komate[i] = tsumekoma[i];
	}

}

void enifu() {
	for(int i = 0; i < 560; i++) {
		if(ekomate[i].empty() == 0) {
			//cout<<"ok\n";
			x = stoi(ekomate[i].substr(0, 4));
			koma = ekomate[i].substr(4, 5);

			a = x / 1000;
			b = (x % 1000) /100;
			c = (x % 100) / 10;
			d = x % 10;

			if(9-a == 0) {
				//cout<<"ok\n";
				for(int j = 0; j < 9; j++) {
					if(board(j)[c] == efu && koma == "FU") {
						ekomate[i] = "";
					}
				}
			}
		}
	}
	for(int i = 0; i < 560; i++) {
		if(ekomate[i].empty() == 0) {
			ekoma_check_num++;
		}
	}
	string etsumekoma[ekoma_check_num];
	int etsumekomaJ = 0;
	for(int i = 0; i < 560; i++) {
		if(ekomate[i].length() > 0) {
			etsumekoma[etsumekomaJ] = ekomate[i];
			etsumekomaJ++;
		}
	}
	for(int i = 0; i < 560; i++) {
		ekomate[i] = "";
	}
	for(int i = 0; i < ekoma_check_num; i++) {
		//cout<<temp[i]<<endl;
		ekomate[i] = etsumekoma[i];
	}

}

void twentyfour() {
	int tfJ = 0;
	for(int i = 0; i < 100; i++) {
		if(ete[i].empty() == 0) {
			new_ete[tfJ] = ete[i];
			tfJ++;
		}  
	}

	/*for(int i = 0; i < 100; i++) {
		if(new_ete[i].empty() == 0) {
			cout<<i<<" "<<new_ete[i]<<endl;
		}
	}*/

	/*tfJ = 0;
	for(int i = 0; i < 100; i++) {
		if(new_ete[i].empty() == 0) {
			ete[tfJ] = new_ete[i];
			tfJ++;
		}  
	}

	for(int i = 0; i < 100; i++) {
		if(new_ete[i].length() != 0) {
			new_ete[i] = "";
		}
	}*/
}

int main() {
	/*sKoma[0] = "FU";
	sKoma[1] = "KI";
	sKoma[2] = "KI";
	eKoma[0] = "FU";
	eKoma[1] = "KI";
	eKoma[2] = "KI";*/
	cout<<"\x1b[H\x1b[2J";
	int count = 1;
	cout<<"<POSITION "<<count<<">";
	while(1) {
		draw();
		op();//junban
		//cout<<"\x1b[H\x1b[2J";
		//cout<<"0"<<eKoma[0]<<endl<<"1"<<eKoma[1]<<endl<<"2"<<eKoma[2]<<endl<<"3"<<eKoma[3]<<endl;
		count++;
		cout<<"<POSITION "<<count<<">";
		draw();
		gameRule();
		//naru();
		//naru();
		//enaru();
		twentyfour();
		//cout<<"24 is "<<ete[23]<<endl;
		//cout<<"24 is "<<new_ete[23]<<endl;
		Koma();
		//ekoma();
		nifu();
		//enifu();
		ekoma();
		enifu();
		cout<<"<LEGAL MOVE>"<<endl;
		for(int nr = 1; nr < 100; nr++) {
			if(te[nr-1].empty() == 0) {
				int i, j = 0;
				//r = nr-1;


				x = stoi(te[nr-1].substr(0, 4));
				koma = te[nr-1].substr(4, 5);

				/*a = x / 1000;
				b = (x % 1000) /100;
				c = (x % 100) / 10;
				d = x % 10;*/

				e = 0;
				f = 0;

				a = x / 1000;
				b = (x % 1000) /100;
				c = (x % 100) / 10;
	   			d = x % 10;
		
	   			b -= 1;
	   			d -= 1;
	   
				e = 0;
				f = 0;
	   			while(f == 0) {
		   			if((c + e) == 9) {
			   			c = e;
			   			f++;
		   			}
		   			e++;
	   			}
		
				i = d;
				j = c;

			cout<<setw(3)<<nr<<"."<</*te[nr-1]*/9-a<<b+2<<c<<d+2<<koma<<" ";
			if(nr % 9 == 0) {
				cout<<endl;
			}
		}
	}
		cout<<endl;
		cout<<"<MOCHIGOMA PUT>"<<endl;
		//cout<<komate[1]<<" "<<komate[559]<<endl;
		for(int mnr = 1; mnr < 560; mnr++) {
			if(komate[mnr-1].empty() == 0) {
				int i, j = 0;

				x = stoi(komate[mnr-1].substr(0, 4));
				koma = komate[mnr-1].substr(4, 5);

				e = 0;
				f = 0;
	   			a = x / 1000;
				b = (x % 1000) /100;
				c = (x % 100) / 10;
				d = x % 10;
		
				b -= 1;
				d -= 1;
		
				e = 0;
				f = 0;
				while(f == 0) {
					if((c + e) == 9) {
						c = e;
						f++;
					}
					e++;
				}
		
				i = d;
				j = c;

			cout<<setw(3)<<mnr<<"."<</*te[nr-1]*/"M"<<"+"<<c<<d+2<<koma<<" ";
			if(mnr % 9 == 0) {
				cout<<endl;
			}
		}
	}
	cout<<endl;
		cout<<"<ENEMY MOVE>"<<endl;
			for(int nr = 1; nr < 100; nr++) {
			//cout<<nr<<" "<<endl;
			if(ete[nr-1].length() != 0) {
				int i, j = 0;
				//r = nr-1;


				x = stoi(ete[nr-1].substr(0, 4));
				koma = ete[nr-1].substr(4, 5);

	
					a = x / 1000;
					b = (x % 1000) /100;
					c = (x % 100) / 10;
					d = x % 10;
		
					b -= 1;
					d -= 1;
		
					e = 0;
					f = 0;
					while(f == 0) {
						if((c + e) == 9) {
							c = e;
							f++;
						}
						e++;
					}
		
					i = d;
					j = c;

					//a += 9-a;
					//b += 2;
					//d += 2;
					
				//}
				

				cout<<setw(3)<<nr<<"."<<9-a<<b+2<<c<<d+2<<koma<<" ";
				if(nr % 9 == 0) {
					cout<<endl;
				}
			}
		}
		cout<<endl;
		cout<<"<ENEMY PUT>"<<endl;
		//cout<<komate[1]<<" "<<komate[559]<<endl;
		for(int mnr = 1; mnr < 560; mnr++) {
			if(ekomate[mnr-1].empty() == 0) {
				int i, j = 0;

				x = stoi(ekomate[mnr-1].substr(0, 4));
				koma = ekomate[mnr-1].substr(4, 5);

				e = 0;
				f = 0;
	   			a = x / 1000;
				b = (x % 1000) /100;
				c = (x % 100) / 10;
				d = x % 10;
		
				b -= 1;
				d -= 1;
		
				e = 0;
				f = 0;
				while(f == 0) {
					if((c + e) == 9) {
						c = e;
						f++;
					}
					e++;
				}
		
				i = d;
				j = c;

			cout<<setw(3)<<mnr<<"."<</*te[nr-1]*/"M"<<"-"<<c<<d+2<<koma<<" ";
			if(mnr % 9 == 0) {
				cout<<endl;
			}
		}
	}
	cout<<endl;
		//cout<<"0"<<eKoma[0]<<endl<<"11"<<eKoma[11]<<endl<<"12"<<eKoma[12]<<endl;//<<"3"<<eKoma[3]<<endl;
		int ekoma_check_kount_disp = 0;
		int etsumeSkomaJ_disp = 0;

		for(int i = 0; i < 40; i++) {
			if(eKoma[i].empty() == 0) {
				ekoma_check_kount_disp++;
			}
		}
		string etsumeSkoma_disp[ekoma_check_kount_disp];
		for(int i = 0; i < 40; i++) {
			if(eKoma[i].length() > 0) {
				etsumeSkoma_disp[etsumeSkomaJ_disp] = eKoma[i];
				etsumeSkomaJ_disp++;
			}
		}
		for(int i = 0; i < 40; i++) {
			eKoma[i] = "";
		}
		for(int i = 0; i < ekoma_check_kount_disp; i++) {
			//cout<<temp[i]<<endl;
			eKoma[i] = etsumeSkoma_disp[i];
		}
		cout<<endl;
		cout<<"<ENEMYS PIECE>"<<endl;
		for(int i = 0; i < 40; i++) {
			if(eKoma[i].length() != 0) {
				cout<<i+1<<"."<<eKoma[i]<<" ";
			}
		}
		cout<<endl;

		//while(f)

		sop();

		count++;
		cout<<"<POSITION "<<count<<">";

		//draw();
		cout<<endl;

		int koma_check_kount_disp = 0;
		int tsumeSkomaJ_disp = 0;

		for(int i = 0; i < 40; i++) {
			if(sKoma[i].empty() == 0) {
				koma_check_kount_disp++;
			}
		}
		string tsumeSkoma_disp[koma_check_kount_disp];
		for(int i = 0; i < 40; i++) {
			if(sKoma[i].length() > 0) {
				tsumeSkoma_disp[tsumeSkomaJ_disp] = sKoma[i];
				tsumeSkomaJ_disp++;
			}
		}
		for(int i = 0; i < 40; i++) {
			sKoma[i] = "";
		}
		for(int i = 0; i < koma_check_kount_disp; i++) {
			//cout<<temp[i]<<endl;
			sKoma[i] = tsumeSkoma_disp[i];
		}

		cout<<"<OWN PIECE>"<<endl;
		for(int i = 0; i < 40; i++) {
			if(sKoma[i].length() != 0) {
				cout<<i+1<<"."<<sKoma[i]<<" ";
			}
			/*if(sKoma[i] == sKoma[i+1] && sKoma[i].empty() == 0) {
				cout<<i+1<<"."<<sKoma[i]<<" ";
			}*/
		}

		for(int i = 0; i < 100; i++) {
			if(te[i].length() != 0) {
				te[i] = "";
			}
		}

		for(int i = 0; i < 560; i++) {
			if(komate[i].length() != 0) {
				komate[i] = "";
			}
		}
		for(int i = 0; i < 100; i++) {
			if(ete[i].length() != 0) {
				ete[i] = "";
			}
		}

		for(int i = 0; i < 560; i++) {
			if(ekomate[i].length() != 0) {
				ekomate[i] = "";
			}
		}
		for(int i = 0; i < 100; i++) {
			if(new_ete[i].length() != 0) {
				new_ete[i] = "";
			}
		}

	}

	cout<<endl;

	return 0;
}
