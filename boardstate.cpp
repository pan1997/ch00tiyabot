//
// Created by pankaj on 20/9/16.
//

#include <bitset>
#include "boardstate.h"
#include "basic.h"
namespace TAK {

    template<int n>
    void boardstate<n>::removeTop(square s) {
        int r = getRow(s);
        int c = getCol(s);
        height[r][c]--;
        if (height[r][c] == 0)
            nempty++;
        peice p = bs[r][c][height[r][c]];
        if (!isCap(p)) if (color_of(p) == WHITE)
            leftover_stones_white++;
        else
            leftover_stones_black++;
        else if (color_of(p) == WHITE)
            leftover_capstones_white++;
        else
            leftover_capstones_black++;
        unsetTopbb(s, p);
    }

    template<int n>
    boardstate<n>::boardstate() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                bs[i][j][0] = NOP;
                height[i][j] = 0;
            }
        turn = WHITE;
        nempty = n * n;
        switch (n) {
            case 4:
                leftover_stones_black = leftover_stones_white = 15;
                leftover_capstones_black = leftover_capstones_white = 0;
                break;
            case 5:
                leftover_stones_black = leftover_stones_white = 21;
                leftover_capstones_black = leftover_capstones_white = 1;
                break;
            case 6:
                leftover_stones_black = leftover_stones_white = 30;
                leftover_capstones_black = leftover_capstones_white = 1;
                break;
            case 7:
                leftover_stones_black = leftover_stones_white = 40;
                leftover_capstones_black = leftover_capstones_white = 1;
                break;
            case 8:
                leftover_stones_black = leftover_stones_white = 50;
                leftover_capstones_black = leftover_capstones_white = 2;
                break;
        }
        WF = BF = WS = BS = WC = BC = 0;
        for (int i = 0; i < 8; i++)
            group_count_W[i] = group_count_B[i] = 0;
        hash = 0;
    }

    template<int n>
    boardstate<n>::boardstate(const boardstate<n> &b) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                height[i][j] = b.height[i][j];
                for (int k = 0; k < height[i][j]; k++)
                    bs[i][j][k] = b.bs[i][j][k];
            }
        turn = b.turn;
        nempty = b.nempty;
        leftover_capstones_black = b.leftover_capstones_black;
        leftover_stones_white = b.leftover_stones_white;
        leftover_capstones_white = b.leftover_capstones_white;
        leftover_stones_black = b.leftover_stones_black;
        WF = b.WF;
        WC = b.WC;
        WS = b.WS;
        BF = b.BF;
        BC = b.BC;
        BS = b.BS;
        for (int i = 0; i < 8; i++) {
            group_count_W[i] = b.group_count_W[i];
            group_count_B[i] = b.group_count_B[i];
        }
        hash = b.hash;
    }

    template<int n>
    void boardstate<n>::place(square s, peice p) {
        int r = getRow(s);
        int c = getCol(s);
        bs[r][c][height[r][c]++] = p;
        if (height[r][c] == 1)
            nempty--;
        if (!isCap(p)) if (color_of(p) == WHITE)
            leftover_stones_white--;
        else
            leftover_stones_black--;
        else if (color_of(p) == WHITE)
            leftover_capstones_white--;
        else
            leftover_capstones_black--;
        setTopbb(s, p);
    }

    template<int n>
    peice boardstate<n>::top(square s) const {
        int r = getRow(s);
        int c = getCol(s);
        return bs[r][c][height[r][c] - 1];
    }

    template<int n>
    peice boardstate<n>::underTop(square s) const {
        int r = getRow(s);
        int c = getCol(s);
        return bs[r][c][height[r][c] - 2];
    }

    template<int n>
    bool boardstate<n>::empty(square s) const {
        int r = getRow(s);
        int c = getCol(s);
        return r < n && c < n && r >= 0 && c >= 0 && height[r][c] == 0;
    }

    template<int n>
    void boardstate<n>::xor_bitboard(square s, peice bb) {
        switch (bb) {
            case WHITE_FLAT:
                WF ^= getBitboard(s);
                break;
            case BLACK_FLAT:
                BF ^= getBitboard(s);
                break;
            case WHITE_STANDING:
                WS ^= getBitboard(s);
                break;
            case BLACK_STANDING:
                BS ^= getBitboard(s);
                break;
            case WHITE_CAP:
                WC ^= getBitboard(s);
                break;
            case BLACK_CAP:
                BC ^= getBitboard(s);
                break;
        }
    }

    template<int n>
    void boardstate<n>::printTo(std::ostream &o) const {
        int mh = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (height[i][j] > mh)
                    mh = height[i][j];
        for (int i = 0; i < n; i++) {
            o << "  ";
            o << '+';
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < mh; k++)
                    o << '-';
                o << '+';
            }
            o << '\n';
            o << n - i << ' ';
            o << '|';
            for (int j = 0; j < n; j++) {
                int k = 0;
                for (; k < height[i][j]; k++)
                    o << bs[i][j][k];
                for (; k < mh; k++)
                    o << ' ';
                o << '|';
            }
            o << '\n';
        }
        o << "  ";
        o << '+';
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < mh; k++)
                o << '-';
            o << '+';
        }
        o << "\n  ";
        for (int i = 0; i < n; i++) {
            o << ' ';
            o << (char) (i + 'a');
            for (int k = 1; k < mh; k++)
                o << ' ';
        }
        o << '\t' << (turn == WHITE ? "WHITE" : "BLACK") << " to move : empty squares " << nempty << ",left (" <<
        leftover_stones_white << ',' << leftover_stones_black << ")\n";
    }

    template<int n>
    bool boardstate<n>::playMove(move m) {
        if (isPlaceMove(m)) {
            hash ^= zobristTable[getRow(m)][getCol(m)][getHeight(m)][getPlacePeice(m)];
            place(m, getPlacePeice(m));
            return false;
        }
        else {
            square s = m;
            direction d = getDirection(m);
            int pick = getPickCount(m);
            m >>= 12;
            unsetTopbb(s, top(s));
            height[getRow(s)][getCol(s)] -= pick;
            if (height[getRow(s)][getCol(s)] == 0)
                nempty++;
            int index = height[getRow(s)][getCol(s)];
            square t = s;
            int count = 0;
            bool res = false;
            for (; pick > 0; count++) {
                int drop = m & 7;
                pick -= drop;
                m >>= 3;
                t = squareAt(t, d);
                if (empty(t))
                    nempty--;
                else {
                    if (pick == 0 && drop == 1 && isStanding(top(t))) {
                        flatten(t);
                        res = true;
                    }
                    unsetTopbb(t, top(t));
                }
                for (int i = 0; i < drop; i++) {
                    hash ^= zobristTable[getRow(s)][getCol(s)][index][bs[getRow(s)][getCol(s)][index]];
                    hash ^= zobristTable[getRow(t)][getCol(t)][height[getRow(t)][getCol(t)]][bs[getRow(s)][getCol(
                            s)][index]];
                    bs[getRow(t)][getCol(t)][height[getRow(t)][getCol(t)]++] = bs[getRow(s)][getCol(s)][index++];
                }
                //setTopbb(t, top(t));
            }
            d = direction(d ^ 1);
            for (; count >= 0; count--) {
                if (!empty(t))
                    setTopbb(t, top(t));
                t = squareAt(t, d);
            }
            return res;
        }
    }

    template<int n>
    void boardstate<n>::undoMove(move m, bool lf) {
        if (isPlaceMove(m)) {
            removeTop(m);
            hash ^= zobristTable[getRow(m)][getCol(m)][getHeight(m)][getPlacePeice(m)];
        }
        else {
            square s = m;
            direction d = getDirection(m);
            int pick = getPickCount(m);
            //unsetTopbb(s,top(s));
            if (height[getRow(s)][getCol(s)] == 0)
                nempty--;
            else unsetTopbb(s, top(s));
            m >>= 12;
            square t = s;
            int count;
            for (count = 0; pick > 0; count++) {
                int drop = m & 7;
                pick -= drop;
                m >>= 3;
                t = squareAt(t, d);
                unsetTopbb(t, top(t));//xor_bitboard(t, top(t));//remove new
                height[getRow(t)][getCol(t)] -= drop;
                if (height[getRow(t)][getCol(t)] == 0)
                    nempty++;
                //else setTopbb(t, top(t));//xor_bitboard(t, top(t));//add prev
                for (int i = 0; i < drop; i++) {
                    hash ^= zobristTable[getRow(s)][getCol(s)][height[getRow(s)][getCol(s)]][bs[getRow(t)][getCol(t)][
                            i + height[getRow(t)][getCol(t)]]];
                    hash ^= zobristTable[getRow(t)][getCol(t)][i + height[getRow(t)][getCol(t)]][bs[getRow(t)][getCol(
                            t)][
                            i + height[getRow(t)][getCol(t)]]];
                    bs[getRow(s)][getCol(s)][height[getRow(s)][getCol(s)]++] = bs[getRow(t)][getCol(t)][i +
                                                                                                        height[getRow(
                                                                                                                t)][getCol(
                                                                                                                t)]];
                }
            }
            d = direction(d ^ 1);
            square end = t;
            for (; count >= 0; count--) {
                if (!empty(t))
                    setTopbb(t, top(t));
                t = squareAt(t, d);
            }
            if (lf) {
                liften(end);
            }
        }
    }
}