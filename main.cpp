//
// Created by pankaj on 20/9/16.
//

#include <iostream>
#include "basic.h"
#include "boardstate.h"
#include "evaluate.h"
#include "search.h"
#include <stack>
#include <cstring>
#include <bitset>
#include <sstream>
#include "autoTuning.h"

void testbug(TAK::boardstate<5> b) {
    //std::string game="e1 a5 Fb1 Fc1 Fc5 Fd1 Fd5 Se5 Fa4 Fb1 Fa1 1b1<1 Fa2 2a1+2 Fa1 Sb2";
    std::string game = "a5 a1 Fb1 Fb5 Cc1 Cb2 Fd1 1b2-1 ";
    game += "Fa2 Sc2 Fb2 Fb3 Fe2 1b3-1 ";
    game += "Fa3 Fa4 Sb4 Fe1 Fc3 Fd4 Fe3 ";
    game += "Fc4 Sc5 1c4>1 Fe4 Fc4 Sd5 1c4>1 ";
    game += "Fd3 Fc4 1d3+1 Fe5 Fd3 1c4>1 1d3+1 Fc4 ";
    game += "1e4<1 1c4>1 Fe4 Sc4 1e4<1 1c4>1 1b4-1";
    /*
1	31	 pv [Fb4 ] (1,85) nodes @86 kNps[0 ms] EBF=1] fatt 0 fsucc 0 ttcuts 0 TT has ? entries and 0 collisions and 0 drops=(0%)
2	0	 pv [Fd2 Fd3 ] (88,928) nodes @112 kNps[8 ms] EBF=9.32738] fatt 0 fsucc 0 ttcuts 0 TT has ? entries and 0 collisions and 0 drops=(0%)
3	38	 pv [Fb4 Fc4 5d4<5 ] (378,7057) nodes @354 kNps[20 ms] EBF=6.61911] fatt 0 fsucc 0 ttcuts 3 TT has ? entries and 0 collisions and 0 drops=(0%)
4	3	 pv [Fd2 Fd3 Fe4 1b3-1 ] (7191,61971) nodes @197 kNps[350 ms] EBF=9.0852] fatt 0 fsucc 0 ttcuts 1156 TT has ? entries and 18 collisions and 0 drops=(0%)
5	16	 pv [Fc4 1b3-1 2b1<2 Fb3 1c2+1 ] (26128,378463) nodes @524 kNps[770 ms] EBF=7.16906] fatt 241 fsucc 71 ttcuts 3967 TT has ? entries and 409 collisions and 1 drops=(0%)
6	0	 pv [Fd3 Fd2 Fc4 Fb4 Fe4 1c5-1 Fc5 ] (347263,2456062) nodes @272 kNps[10268 ms] EBF=8.27525] fatt 5257 fsucc 4233 ttcuts 114491 TT has ? entries and 23613 collisions and 394 drops=(1%)

     2.1
1	[Fd2 Fd3  #(-4)]-4 (1,217) nodes @109 kNps[1 ms] EBF=1 0% of 0 nmt TT drops 0% of 0 colls
2	[Fd2 Fd3  #(-4)]-4 (87,345) nodes @72 kNps[5 ms] EBF=9.27362 0% of 0 nmt TT drops 0% of 0 colls
3	[Fd3 1b3-1 Fd2 Fb3  #(-40)]-40 (448,13281) nodes @371 kNps[36 ms] EBF=7.12037 0% of 0 nmt TT drops 0% of 0 colls
4	[Fd3 1b3-1 Fd2 Fb3  #(-40)]-40 (4020,20648) nodes @160 kNps[153 ms] EBF=7.73086 44% of 84 nmt TT drops 0% of 0 colls
5	[Fd3 Fd2 Fe4 1b3-1 Fc4 1e3<1  #(-47)]-47 (11420,274439) nodes @376 kNps[758 ms] EBF=5.94082 45% of 239 nmt TT drops 0% of 0 colls
6	[Fd3 Fd2 Fe4 1b3-1 Fc4 1e3<1  #(-47)]-47 (73374,441029) nodes @186 kNps[2751 ms] EBF=6.2904 61% of 2655 nmt TT drops 0% of 1 colls
7	[Fd3 1b3-1 Fe4 Fb3 Fb4 1e3<1 1c2+1 Fd2  #(-23)]-23 (167522,3620214) nodes @389 kNps[9712 ms] EBF=5.13505 62% of 5816 nmt TT drops 0% of 399 colls
8	[Fd3 1b3-1 Fe4 Fd2 Fc4 Fb4 1c2>1 1b4<1  #(-24)]-24 (1109489,6557429) nodes @176 kNps[43377 ms] EBF=5.58155 64% of 38704 nmt TT drops 4% of 2719 colls
     */


    std::string game1 = "a5 a1 Fa2 Fb5 Fb2 Sc2 Cc1 Fe1 Fd1 ";
    game1 += "Fe5 Fe2 Fd4 Fe3 Fc4 Fa3 1c4>1 Sc5 Fe4 Sd5 1e4<1 ";
    game1 += "Fc4 Fe4 1c4>1 1e4<1 Fc4 Fe4 1c4>1 Fa4 Fc4 Fb3 ";
    game1 += "1c4>1 1b3-1 Fb3 1e4<1 1b3-1 Ce4 Fc4 Fd3 1c4>1 ";
    game1 += "1d3+1 Fc3 1e4<1 Fb4 1d4>1 Fc4 1e4<1 Fb3 1d4>1 1b3>1 1e4<1 ";

    std::string game2 = "e1 a5 Fb5 Cb4 Fa2 Fe3 Fa3 Fa4 Fc4 Fc5 Fd5 Fd4 ";
    game2 += "Fe5 1b4>1 1a5-1 Fe2 1b5>1 2c4+2 Ca5 ";


    std::string game4="e1 a1 Fa2 Fb4 Fb2 Fc2 Cb3 Fa4 Fc3 Cc4 ";
    game4+="1b3+1 Fb5 Fb3 1c4-1 Fc4 2c3<2 Fd4 Fa3 Fe4 Fc3 1a2+1 3b3<3 ";

    game4+="Fb1 Fb3 Fa5 ";
    game4+="1b5<1 2b4-2 Fb4 Fd3 1c2<1 Fd2 Fc1 3b3-3 5a3-14 ";
    game4+="4b2<4 Sc2 Fb3 1c3<1 Fd1 1c2>1 Fc2";
    //game2+="Sa1 ";
    /*
     * Current
1	-65	 pv [Fa1 ] (1,97) nodes @98 kNps[0 ms] EBF=1] fatt 0 fsucc 0 ttcuts 0 TT has ? entries and 0 collisions and 0 drops=(0%)
2	-69	 pv [Fa1 Fb2 ] (71,952) nodes @341 kNps[2 ms] EBF=8.3666] fatt 0 fsucc 0 ttcuts 15 TT has ? entries and 0 collisions and 0 drops=(0%)
3	-71	 pv [Fa1 Fb2 Fb1 ] (243,4787) nodes @718 kNps[6 ms] EBF=5.5613] fatt 0 fsucc 0 ttcuts 57 TT has ? entries and 0 collisions and 0 drops=(0%)
4	-97	 pv [Fa1 Fb2 Fb1 Fc2 ] (3698,23198) nodes @401 kNps[66 ms] EBF=7.66676] fatt 0 fsucc 0 ttcuts 1199 TT has ? entries and 1 collisions and 0 drops=(0%)
5	-116 pv [Fa1 Fb2 Fb1 Fc1 1a1+1 Fb3 1b1+1 ] (11216,140565) nodes @811 kNps[186 ms] EBF=5.95965] fatt 95 fsucc 30 ttcuts 3577 TT has ? entries and 51 collisions and 0 drops=(0%)
6	-98	 pv [Sa1 Fb2 1a1+1 Fb3 2a2+11 Fd3 Fe4 1d3>1 ] (152722,925794) nodes @451 kNps[2386 ms] EBF=7.21876] fatt 2138 fsucc 1455 ttcuts 68287 TT has ? entries and 2642 collisions and 20 drops=(0%)
7	-25	 pv [Sa1 Fb2 1a1+1 Fb3 2a2+11 Fb4 4c5>13 ] (382854,3952366) nodes @818 kNps[5294 ms] EBF=5.83441] fatt 5169 fsucc 3538 ttcuts 217326 TT has ? entries and 29362 collisions and 773 drops=(2%)
8	17	 pv [Sa1 Fb2 1a1+1 Fb3 2a2+11 1d5-1 4c5>13 Fe4 4e5-4 ] (1000457,8636558) nodes @570 kNps[16879 ms] EBF=5.29467] fatt 14302 fsucc 10456 ttcuts 562452 TT has ? entries and 188452 collisions and 9331 drops=(4%)
     2.1
1	[Fa1 Fb2  #(-143)]-143 (1,409) nodes @205 kNps[1 ms] EBF=1 0% of 0 nmt TT drops 0% of 0 colls
2	[Fa1 Fb2  #(-143)]-143 (71,516) nodes @195 kNps[2 ms] EBF=8.3666 0% of 0 nmt TT drops 0% of 0 colls
3	[Fa1 Fb2 1a1+1 Fb3  #(-171)]-171 (253,12518) nodes @425 kNps[29 ms] EBF=5.66705 0% of 0 nmt TT drops 0% of 0 colls
4	[Fa1 Fb2 1a1+1 Fb3  #(-171)]-171 (2332,16977) nodes @332 kNps[57 ms] EBF=6.75248 26% of 40 nmt TT drops 0% of 0 colls
5	[Sa1 Fb2 1a1+1 Fb3 2a2+11 Fb4  #(-140)]-140 (6266,148438) nodes @457 kNps[337 ms] EBF=5.2356 65% of 232 nmt TT drops 0% of 0 colls
6	[Sa1 Fb2 1a1+1 Fb3 2a2+11 Fc3  #(-135)]-141 (16149,186181) nodes @412 kNps[489 ms] EBF=4.63249 63% of 566 nmt TT drops 0% of 0 colls
7	[Sa1 Fb2 1a1+1 Fb3 2a2+11 1d5-1 Fe4 1e5-1  #(-28)]-28 (34826,647402) nodes @502 kNps[1357 ms] EBF=4.07555 75% of 2018 nmt TT drops 0% of 0 colls
8	[Sa1 Fb2 1a1+1 Fb3 2a2+11 1d5-1 Fe4 1e5-1  #(-28)]-28 (72805,951162) nodes @499 kNps[2050 ms] EBF=3.73631 82% of 5373 nmt TT drops 0% of 0 colls
9	[Sa1 Fb2 1a1+1 Fb3 2a2+11 Fd2 4c5>13 1d2>1 2a4-2 Fb4  #(-42)]-42 (384405,7263440) nodes @503 kNps[15198 ms] EBF=4.07755 77% of 22725 nmt TT drops 0% of 2387 colls

     */

    std::string game3 = "a1 e1 Fe2";
    std::stringstream moves(game2);
    std::cout << "Tesing bug\n";
    //std::strcpy(mv[16],"1a1+1")

    char tm[20];
    moves >> tm;
    std::cout << "placing " << tm << '\n';
    b.playMove(TAK::construct_place_move(TAK::readSquare(tm), TAK::BLACK_FLAT));
    std::cout << "placed\n";
    std::cout << b << '\n';
    moves >> tm;
    std::cout << "placing " << tm << '\n';
    b.playMove(TAK::construct_place_move(TAK::readSquare(tm), TAK::WHITE_FLAT));
    std::cout << b << '\n';

    for (int i = 2; moves >> tm; i++) {
        std::cout << "Move " << tm << '\n';
        std::cout << std::bitset<64>(b.getHash()) << '\n';
        b.playMove(TAK::readMove(tm, b.getTurn()));
        b.undoMove(TAK::readMove(tm, b.getTurn()));
        std::cout << std::bitset<64>(b.getHash()) << '\n';
        b.playMove(TAK::readMove(tm, b.getTurn()));
        b.flipTurn();
        std::cout << b << '\n';
    }
    //b.flipTurn();
    std::cout << b << '\n';
    int ms = 0, mse = 0;
    //mse = TAK::evaluateStacks(b);
    if(b.end()){
        std::cout<<"end "<<TAK::terminalEval(b)<<'\n';
    }

    TAK::printBitboard(std::cout,TAK::spread[3][3][2][0]);
    TAK::move m = TAK::search(b, ms, 450000, 360000);
    std::cout << ms << ' ' << mse << " done\n";
    std::cout << b << '\n';
}

template<int n>int n_cui() {
    using namespace TAK;
    boardstate<n> b;
    std::string cmd;
    std::cout<<"playing on size "<<n<<'\n';
    while (std::cin >> cmd) {
        if (cmd == "clear")
            b.clear();
        else if (cmd == "play") {
            char buf[200];
            std::cin >> buf;
            move m = readMove(buf, b.getTurn());
            std::cout<<"playing "<<buf<<' ';
            printMove(std::cout,m);
            std::cout<<' '<<std::bitset<64>(m);
            std::cout<<'\n';
            bool fl = b.playMove(m);
            b.flipTurn();
        }
        else if (cmd == "analyse") {
            int tl, ans;
            std::cin >> tl;
            move m = search(b, ans, tl);
            std::cout << "BEST MOVE ";
            printMove(std::cout, m);
            std::cout << " score " << ans << '\n';
        }
        else if (cmd == "size") {
            int x;
            std::cin >> x;
            if (n == x)
                b.clear();
            else return x;
        }
        else if (cmd == "exit") {
            return 0;
        }
        else if (cmd == "board") {
            std::cout << b << '\n';
        }
    }
}
void cui() {
    std::cout<<"ch00tiyaBOT CUI\n";
    std::cout << "default start size 5\n";
    int x = 5;
    for (; x != 0;) {
        switch (x) {
            case 4:
                x = n_cui<4>();
                break;
            case 5:
                x = n_cui<5>();
                break;
            case 6:
                x = n_cui<6>();
                break;
            case 7:
                x = n_cui<7>();
                break;
            default:
                std::cout << "Cannot play on size " << x << " restaring for 5\n";
                x = 5;
                break;
        }
    }
}

template <int n> void assignment(TAK::boardstate<n> board,int p,int limit,int increment=0) {
    using namespace TAK;
    initZobrist();
    initGroups(n);
    initSlides();
    initbasic(n);
    initCitadels();
    initInfo(n);
    initSpread();
    transpositionTableInit();
    p -= 1;
    char tm[50];
    std::string mv = "Fa";
    tm[1] = 0;
    tm[0] = '1';
    mv.append(tm);
    if (p == 0) {
        std::strcpy(tm, mv.c_str());
        std::cout << tm << "\n";
        board.playMove(construct_place_move(readSquare(tm + 1), BLACK_FLAT));
        std::cin >> tm;
        board.playMove(construct_place_move(readSquare(tm + 1), WHITE_FLAT));
    }
    else {
        std::cin >> tm;
        board.playMove(construct_place_move(readSquare(tm + 1), BLACK_FLAT));
        if (std::strcmp(tm, mv.c_str()) != 0)
            std::strcpy(tm, mv.c_str());
        else {
            std::strcpy(tm, "Fa0");
            tm[2] += n;
            tm[1] += (n - 1);
        }
        std::cout << tm << "\n";
        board.playMove(construct_place_move(readSquare(tm + 1), WHITE_FLAT));
    }
    move m;
    for (int i = 0; ; i++) {
        std::cerr << board << '\n';
        int mx = 0;
        if (i % 2 == p) {
            int aim = int(limit / (board.countEmpty() * 1.4 + 3));
            std::cerr << "aiming " << aim << " ms\n";
            auto start = std::chrono::system_clock::now();
            m = search(board, mx, aim, std::min(limit / 3, 120000));
            auto end = std::chrono::system_clock::now();
            printMove(std::cout, m);
            limit -= std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << '\n';
            std::cout.flush();
            limit += increment;
            std::cerr << "Left " << limit << " ms\n";
        }
        else {
            std::cin >> tm;
            m = readMove(tm, board.getTurn());
        };
        board.playMove(m);
        board.flipTurn();
        if (board.end()) {
            return;
        }
    }
}
int main() {
    using namespace std;
    srand(time(NULL));
    cerr << "ch00tiyaBOT 2.3.0\n";
    int p, n, lim;
    cerr << "Enter p n lim\n";
    cin >> p >> n >> lim;
    //lim = 120;
    //p=n=lim=1;
    int increment = 0 * 1000;
    lim *= 1000;
    switch (n) {
        case 4:
            assignment(TAK::boardstate<4>(), p, lim, increment);
            break;
        case 5:
            assignment(TAK::boardstate<5>(), p, lim, increment);
            break;
        case 6:
            assignment(TAK::boardstate<6>(), p, lim, increment);
            break;
        case 7:
            assignment(TAK::boardstate<7>(), p, lim, increment);
            break;
        case 8:
            std::cout << "not programmed for " << n << ", ask for a special version for this from the programmer\n";
            assignment(TAK::boardstate<8>(), p, lim, increment);
            break;
        default:
            //TAK::tune();
            //cui();
            std::cout << "game not defined. Just autotuning/bug fixing\n";
            TAK::initZobrist();
            TAK::initGroups(5);
            TAK::initInfo(5);
            TAK::initSlides();
            TAK::initbasic(5);
            TAK::initSpread();
            TAK::initCitadels();
            TAK::transpositionTableInit();
            TAK::boardstate<5> b;
            testbug(b);

    }
    return 0;
}