#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define board(a) (_board+(a)*9)
#define outofrange cout<<"Something went wrong around "<<__func__<<"("<<__LINE__<<") (out of range)"<<endl
#define TE_MAX 300
#define sette(t,from_i,from_j,to_i,to_j,koma) if(*t < TE_MAX)t[++*t]=(koma)*81*81+((from_i)*9+(from_j))*81+(to_i)*9+(to_j);else outofrange
#define sete(t,to_i,to_j) sette(t,i,j,to_i,to_j,abs(board(i)[j]))
#define isc(a) (a < 0)
#define isp(a) (a > 0)
#define to_c -
#define to_p +

using namespace std;

enum {
	em, emp=0,
	fu, ky, ke, gi, ki, ka, hi,
	to, ny, nk, ng,     um, ry, gy,

	pfu = to_p(fu), pky = to_p(ky), pke = to_p(ke), pgi = to_p(gi), pki = to_p(ki), pka = to_p(ka), phi = to_p(hi),
	pto = to_p(to), pny = to_p(ny), pnk = to_p(nk), png = to_p(ng),                 pum = to_p(um), pry = to_p(ry), pgy = to_p(gy),

	cfu = to_c(fu), cky = to_c(ky), cke = to_c(ke), cgi = to_c(gi), cki = to_c(ki), cka = to_c(ka), chi = to_c(hi),
	cto = to_c(to), cny = to_c(ny), cnk = to_c(nk), cng = to_c(ng),                 cum = to_c(um), cry = to_c(ry), cgy = to_c(gy),
};

string FU = "FU", KY = "KY", KE = "KE", GI = "GI", KI = "KI", KA = "KA", HI = "HI",
       TO = "TO", NY = "NY", NK = "NK", NG = "NG",            UM = "UM", RY = "RY", GY = "GY";

int _board[81] = {
	cky, cke, cgi, cki, cgy, cki, cgi, cke, cky,
	emp, chi, emp, emp, emp, emp, emp, cka, emp,
	cfu, cfu, cfu, cfu, cfu, cfu, cfu, cfu, cfu,
	emp, emp, emp, emp, emp, emp, emp, emp, emp,
	emp, emp, emp, emp, emp, emp, emp, emp, emp,
	emp, emp, emp, emp, emp, emp, emp, emp, emp,
	pfu, pfu, pfu, pfu, pfu, pfu, pfu, pfu, pfu,
	emp, pka, emp, emp, emp, emp, emp, phi, emp,
	pky, pke, pgi, pki, pgy, pki, pgi, pke, pky,
};

int pte[TE_MAX+1];
int cte[TE_MAX+1];
int pkoma[7];
int ckoma[7];
int game_count;

int s2cKoma(string koma) {
	     if(koma == "FU") return cfu;
	else if(koma == "KY") return cky;
	else if(koma == "KE") return cke;
	else if(koma == "GI") return cgi;
	else if(koma == "KI") return cki;
	else if(koma == "KA") return cka;
	else if(koma == "HI") return chi;
	else if(koma == "TO") return cto;
	else if(koma == "NY") return cny;
	else if(koma == "NK") return cnk;
	else if(koma == "NG") return cgi;
	else if(koma == "UM") return cka;
	else if(koma == "RY") return chi;
	else if(koma == "GY") return cgy;
	return 0;
}

#define s2pKoma(koma) (-s2cKoma(koma))

int nariKind(int koma) {
	switch(abs(koma)){
		case fu: return to;
		case ky: return ny;
		case ke: return nk;
		case gi: return ng;
		case ka: return um;
		case hi: return ry;
		default: return em;
	}
}

int naru(int koma) {
	int k = nariKind(koma);
	return k ? k : koma;
}

int unNaru(int koma) {
	switch(abs(koma)){
		case to: return fu;
		case ny: return ky;
		case nk: return ke;
		case ng: return gi;
		case um: return ka;
		case ry: return hi;
		default: return abs(koma);
	}
}

string komaName(int koma) {
	switch(abs(koma)) {
		case fu: return FU;
		case ky: return KY;
		case ke: return KE;
		case gi: return GI;
		case ki: return KI;
		case ka: return KA;
		case hi: return HI;
		case to: return TO;
		case ng: return NG;
		case um: return UM;
		case ry: return RY;
		case gy: return GY;
		default: return "";
	}
}

#define komaCoor(i,j) komaName(board(i)[j])

void draw() {
	cout<<endl<<" 9  8  7  6  5  4  3  2  1 "<<endl;
	int v;
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if((v=board(i)[j])==0) {
				cout<<" * ";
			} else {
				cout<<(isp(v)?"+":"-");
				switch(abs(v)) {
					case fu: cout<<"歩"; break;
					case ky: cout<<"香"; break;
					case ke: cout<<"桂"; break;
					case gi: cout<<"銀"; break;
					case ki: cout<<"金"; break;
					case ka: cout<<"角"; break;
					case hi: cout<<"飛"; break;
					case to: cout<<"と"; break;
					case ny: cout<<"杏"; break;
					case nk: cout<<"圭"; break;
					case ng: cout<<"全"; break;
					case um: cout<<"馬"; break;
					case ry: cout<<"竜"; break;
					case gy: cout<<"玉"; break;
				}
			}
		}
		cout<<" "<<i+1<<endl;
	}
	cout<<"ckoma:";
	for(int i = 0, l = 0; i < sizeof(ckoma)/sizeof(ckoma[0]); i++) {
		string k = komaName(i+1);
		for(int j = 0; j < ckoma[i]; j++) {
			cout<<" "<<k;
			if(++l == 10) {
				cout<<endl<<"      ";
				l=0;
			}
		}
	}
	cout<<endl<<"pkoma:";
	for(int i = 0, l = 0; i < sizeof(pkoma)/sizeof(pkoma[0]); i++) {
		string k = komaName(i+1);
		for(int j=0; j<pkoma[i]; j++) {
			cout<<" "<<k;
			if(++l == 10) {
				cout<<endl<<"      ";
				l=0;
			}
		}
	}
	cout<<endl<<endl;
}

void moveto(int i, int j, int s, int ud, int rl) {
	int*t,flag;
	     if(isp(board(i)[j])) { t=pte; flag= 1; ud*=-1; }
	else if(isc(board(i)[j])) { t=cte; flag=-1; }
	for(int k = 1; k <= s; k++) {
		if((ud == -1 ? i-k >= 0 : ud == 1 ? i+k < 9 : true) &&
		   (rl == -1 ? j-k >= 0 : rl == 1 ? j+k < 9 : true) &&
		   board(i+k*ud)[j+k*rl]*flag <= 0) {
			sete(t,i+k*ud,j+k*rl);
			if(board(i+k*ud)[j+k*rl]) break;
		}else break;
	}
}

void keTobi(int i, int j, int s) {
	if(isp(board(i)[j]) && i-2>=0) {
		if(j-1 >= 0 && board(i-2)[j-1] < 0) { sete(pte,i-2,j-1); }
		if(j+1 <= 9 && board(i-2)[j+1] < 0) { sete(pte,i-2,j+1); }
	}
	if(isc(board(i)[j]) && i+2<=9) {
		if(j-1 >= 0 && board(i+2)[j-1] > 0) { sete(cte,i+2,j-1); }
		if(j+1 <= 9 && board(i+2)[j+1] > 0) { sete(cte,i+2,j+1); }
	}
}

void above           (int i, int j, int s) { moveto(i, j, s,  1,  0); }
void below           (int i, int j, int s) { moveto(i, j, s, -1,  0); }
void left_and_right  (int i, int j, int s) { moveto(i, j, s,  0,  1);
                                             moveto(i, j, s,  0, -1); }
void diagonally_above(int i, int j, int s) { moveto(i, j, s,  1,  1); 
                                             moveto(i, j, s,  1, -1); }
void diagonally_below(int i, int j, int s) { moveto(i, j, s, -1,  1); 
                                             moveto(i, j, s, -1, -1); }

int checkmove(int from_i,int from_j,int to_i,int to_j,int koma) {
	return 1;
	int from_koma = board(from_i)[from_j];
	int flag = from_koma > 0 ? 1 : -1;
	from_koma = abs(from_koma);
	if(from_koma != koma &&
	   nariKind(from_koma) != koma &&
	   !( flag==1 ? (from_i<3 || to_i<3) : (from_i>5 || to_i>5) ) ) {
		cout<<"You can't naru "<<komaName(from_koma)<<" into "<<komaName(koma)<<"."<<endl;
		return 0;
	}
	koma = from_koma;
	switch(koma) {
		case to: case ny: case nk: case ng:
			koma = ki; break;
		case ke:
			if(to_i==4-3*flag) {
				cout<<komaName(koma)<<" won't be able to move."<<endl;
				return 0;
			}
		case fu: case ky:
			if(to_i==4-4*flag) {
				cout<<komaName(koma)<<" won't be able to move."<<endl;
				return 0;
			}
	}
	if(board(to_i)[to_j] && ( isp(flag) == isp(board(to_i)[to_j]) ) ) {
		cout<<"You can't move into your own koma."<<endl;
		return 0;
	}
	if(from_j == to_j) {
		int f = from_i<to_i ? 1 : -1;
		if(f != flag) {
			if(from_i-to_i == flag) {
				switch(koma) {
					case fu: case gi: return 1;
				}
			}
			if(koma == ky) {
				for(int i = from_i+f; i != to_i; i+=f) {
					if(board(i)[from_j]) {
						cout<<"You can't move via koma."<<endl;
						return 0;
					}
				}
				return 1;
			}
		}
		if(abs(from_i-to_i) == 1) {
			switch(koma) {
				case ki: case um: case gy:
					return 1;
			}
		}
		switch(koma) {
			case hi: case ry:
				for(int i = from_i+f; i != to_i; i+=f) {
					if(board(i)[from_j]) {
						cout<<"You can't move via koma."<<endl;
						return 0;
					}
				}
				return 1;
		}
	} else if(from_i == to_i) {
		int f = from_j<to_j ? 1 : -1;
		if(abs(from_j-to_j) == 1) {
			switch(koma) {
				case ki: case um: case gy:
					return 1;
			}
		}
		switch(koma) {
			case hi: case ry:
				for(int j = from_j+f; j != to_j; j+=f) {
					if(board(from_i)[j]) {
						cout<<"You can't move via koma."<<endl;
						return 0;
					}
				}
				return 1;
		}
	} else if(abs(from_i-to_i) == abs(from_j-to_j)) {
		if(abs(from_i-to_j) == 1) {
			if(koma == ki && to_i-from_i == flag) {
				cout<<"Move mismatch.";
				return 0;
			}
			switch(koma){
				case gi: case ki: case ry:
					return 1;
			}
		}
		switch(koma){
			case ka: case um:
				int fi = from_i<to_i ? 1 : -1;
				int fj = from_j<to_j ? 1 : -1;
				for(int i = from_i+fi, j = from_j+fj; i != to_i; i+=fi, j+=fj){
					if(board(i)[j]) {
						cout<<"You can't move via koma."<<endl;
						return 0;
					}
				}
				return 1;
		}
	} else {
		return koma==ke &&
		       abs(from_i-to_i)==2 &&
		       abs(from_j-to_j)==1 &&
		       ( (from_i>to_i) == (flag==1) );
	}
	cout<<"Move mismatch."<<endl;
	return 0;
}

int pKoma(int i, int j, int k) {
	if(isc(board(i)[j])) {
		if(board(i)[j]==cgy){
			cout<<endl<<"*** YOU WIN! ***"<<endl;
			exit(0);
		}
		pkoma[unNaru(abs(board(i)[j]))-1]++;
	} else if(isp(board(i)[j])) return 0;
	board(i)[j] = abs(k);
	return 1;
}

int cKoma(int i, int j, int k) {
	if(isp(board(i)[j])) {
		if(board(i)[j]==pgy) {
			cout<<endl<<"** YOU LOSE ***"<<endl;
			exit(0);
		}
		ckoma[unNaru(board(i)[j])-1]++;
	} else if(isc(board(i)[j])) return 0;
	board(i)[j] = -abs(k);
	return 1;
}

/*
void pnaru() {
	for(int i = 0; i < 100; i++) {
		if(pte[i]/81%9<3 || pte[i]%9<3) {
			if(*pte < TE_MAX) {
				int k=pte[i]/6561;
				pte[k==gi||(k==ke||k==ky)&&pte[i]/729%9==3
					?++*pte:i] = pte[i]%6561+naru(k)*6561;
			} else outofrange;
		}
	}
}
*/

void cnaru() {
	for(int i = 0; i < 100; i++) {
		if(cte[i]/9/9/9%9>5 || cte[i]/9%9>5) {
			if(*cte < TE_MAX) {
				int k=cte[i]/6561;
				cte[k==gi||(k==ke||k==ky)&&cte[i]/729%9==6
					?++*cte:i] = cte[i]%6561+naru(k)*6561;
			} else outofrange;
		}
	}
}

void gameRule(int flag) {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(board(i)[j]*flag > 0) {
				switch(abs(board(i)[j])) {
					case fu:
						above           (i, j, 1); break;
					case ky:
						above           (i, j, 9); break;
					case ke:
						keTobi          (i, j, 1); break;
					case gi:
						above           (i, j, 1);
						diagonally_above(i, j, 1);
						diagonally_below(i, j, 1); break;
					case to: case ny: case nk: case ng: case ki:
						above           (i, j, 1);
						below           (i, j, 1);
						diagonally_above(i, j, 1);
						left_and_right  (i, j, 1); break;
					case um:
						above           (i, j, 1);
						below           (i, j, 1);
						left_and_right  (i, j, 1); /***FALLTHROUGH***/
					case ka:
						diagonally_above(i, j, 9);
						diagonally_below(i, j, 9); break;
					case ry:
						diagonally_above(i, j, 1);
						diagonally_below(i, j, 1); /***FALLTHROUGH***/
					case hi:
						above           (i, j, 9);
						below           (i, j, 9);
						left_and_right  (i, j, 9); break;
					case gy:
						above           (i, j, 1);
						below           (i, j, 1);
						left_and_right  (i, j, 1);
						diagonally_above(i, j, 1);
						diagonally_below(i, j, 1); break;
				}
			}
		}
	}
}

#define cGameRule() gameRule(to_c(1))
#define pGameRule() gameRule(to_p(1))

void pop() {
	string t,k;
	int a,b,c,d,x;
	while(true){
		cout<<"Black >";
		cin>>t;
		cout<<t<<endl;
		if(t=="exit") {
			cout<<"exiting..."<<endl;
			exit(0);
		}
		if(t=="skip" && game_count==1) {
			cout<<"Skipped first turn."<<endl;
			return;
		}
		a =  '9' - t[0];
		b = t[1] -  '1';
		c =  '9' - t[2];
		d = t[3] -  '1';
		k = t.substr(4,2);
		if(a==9 && b==-1) {
			int i = s2pKoma(k);
			if(!pkoma[i-1]){
				cout<<k<<" was not found."<<endl;
				continue;
			}
			switch(i){
				case fu:
					{
						int f = 0;
						for(int i = a; i < 81; i += 9) {
							if(board(i)[c] == pfu) {
								cout<<"nifu"<<endl;
								f=1;break;
							}
						}
						if(f)continue;
					}
				case ke: case ky:
					if(!c || i==ke && c==1){
						cout<<k<<" won't be able to move.";
						continue;
					}
			}
			if(!pKoma(d, c, i)) {
				cout<<"invalid move."<<endl;
				continue;
			}
			pkoma[i-1]--;
			return;
		}
		if(!checkmove(b, a, d, c, x=s2pKoma(k))) {
			cout<<"invalid move."<<endl;
			continue;
		}
		pKoma(d, c, x);
		board(b)[a] = emp;
		return;
	}
}

void cop() {
	cGameRule();
	cnaru();
	cout<<"<COMPUTER'S MOVE>"<<endl;
	for(int nr = 1; nr <= *cte; nr++) {
		int k = cte[nr] / 9 / 9 / 9 / 9;
		int a = cte[nr] / 9 / 9 / 9 % 9;
		int b = cte[nr] / 9 / 9 % 9;
		int c = cte[nr] / 9 % 9;
		int d = cte[nr] % 9;
		cout<<setw(3)<<nr<<"."<<9-b<<a+1<<9-d<<c+1<<komaName(k)<<" ";
		if(nr % 9 == 0) cout<<endl;
	}
	cout<<endl;
	string t;
	srand(time(0UL));
	int sum = 0;
	for(int i = 0;i < sizeof(ckoma)/sizeof(ckoma[0]); i++) {
		sum += ckoma[i];
	}
	int r = rand() % (*cte + sum);
	if(r+1 <= *cte) {
		int k = cte[r+1] / 9 / 9 / 9 / 9;
		int a = cte[r+1] / 9 / 9 / 9 % 9;
		int b = cte[r+1] / 9 / 9 % 9;
		int c = cte[r+1] / 9 % 9;
		int d = cte[r+1] % 9;
		cout<<endl<<"White >"<<r+1<<"."<<9-b<<a+1<<9-d<<c+1<<komaName(k)<<endl;
		cKoma(c, d, k);
		board(a)[b] = emp;
	} else while(true) {
		int x = rand() % 567;
		int i = x / 9 % 9;
		int j = x % 9;
		x = ckoma[x / 9 / 9];
		switch(x) {
			case fu:
				{
					int f = 0;
					for(int k = i; k < 81; k += 9) {
						if(_board[k] == cfu) {
							f=1;
							break;
						}
					}
					if(f) continue;
				}
			case ke: case ky:
				if(i==8||x==ka&&i==7) continue;
		}
		if(cKoma(i, j, x)) {
			cout<<endl<<"White >"<<"M"<<"+"<<9-j<<i+1<<komaName(x)<<endl;
			break;
		}
	}
	*pte=0;
	*cte=0;
}

int main() {
	cout<<"\x1b[H\x1b[2J";
	game_count = 0;
	while(1) {
		cout<<"<POSITION "<<++game_count<<">"<<endl;
		draw();
		pop();
		cout<<"<POSITION "<<++game_count<<">"<<endl;
		draw();
		cop();
		game_count++;
	}
}
