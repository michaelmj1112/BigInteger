#pragma once
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

using namespace std;
class BigInteger
{
public:
    BigInteger() {
        length = 0;
        sign = 1;
    }; // default constructor
    BigInteger(BigInteger& n) {
        sign = n.sign;
        length = n.length;
        digits = new int[length];

        for (int i = 0; i < length; i++) {
            digits[i] = n.digits[i];
        }
    }; // copy constructor
    BigInteger(string str) {
        length = str.length();
        if (str[0] == '-')
            sign = -1;
        else
            sign = 1;

        digits = new int[length];

        int j = 0;
        for (int i = 0; i < length; i++) {
            if (str[i] == '-')
                continue;

            else {
                digits[j] = str[i]-'0';
                j++;
            }
        }
        length = j;
    }; // constructor with initialization using a specified string of digits
    bool isZero() {
        for (int i = 0; i < length; i++) {
            if (digits[i] != 0)
                return false;
        }

        return true;
    }; // check if the big integer is zero
    int size() { return length; } // return the length of the big integer
    BigInteger operator +(BigInteger& n) {
        string result;
        int top, bot; /*to act as a replacement for 0 if the length of
        2 BigIntegers are not the same*/
        int rSign; //acts as a new sign for result
        BigInteger AbsCurr = *this;
        BigInteger AbsN = n;
        AbsCurr = Abs(AbsCurr);
        AbsN = Abs(AbsN);


        if (sign == n.sign) {
            for (int i = length - 1, j = n.size() - 1, carry = 0; i >= 0 || j >= 0 || carry; i--, j--) {
                if (i >= 0)
                    top = digits[i];
                else
                    top = 0;

                if (j >= 0)
                    bot = n.digits[j];
                else
                    bot = 0;

                int sum = top + bot + carry;

                if (sum > 9) {
                    carry = 1; /*carry acts as temporary place to store the value of
                    1 when sum is a double digit number*/
                    result += '0'+(sum%10);
                }
                else {
                    carry = 0;
                    result += '0'+(sum);
                }
            }
            rSign = sign == 1 ? 1 : -1;
            reverse(result.begin(), result.end());
            result.erase(0, result.find_first_not_of('0')); //erasing any first 0s
            BigInteger r(result);
            r.sign = rSign;
            return r;
        }

        //operator -
        else if (sign != n.sign) {
            if (AbsCurr == AbsN) {
                BigInteger r("0");
                return r;
                //if one is positive and one is negative and their value are the same
            }

            else if (AbsCurr > AbsN) {
                for (int i = AbsCurr.length - 1, j = n.size() - 1, borrow = 0; i >= 0 || j >= 0; i--, j--) {
                    if (i >= 0)
                        top = AbsCurr.digits[i];
                    else
                        top = 0;

                    if (j >= 0)
                        bot = n.digits[j];
                    else
                        bot = 0;

                    int sum = top - bot;

                    if (sum < 0) {
                        borrow = 10;
                        sum = top + borrow - bot;
                        if (i != 0)
                            AbsCurr.digits[i-1] -= 1; //borrowing from the next digit
                        result += '0'+(sum);
                    }
                    else
                        result += '0'+(sum);
                }
                rSign = (sign == 1) ? 1 : -1;
                reverse(result.begin(), result.end());
                result.erase(0, result.find_first_not_of('0'));
                BigInteger r(result);
                r.sign = rSign;
                return r;
            }

            else if (AbsCurr < AbsN) {
                for (int i = AbsN.size() - 1, j = length - 1, borrow = 0; i >= 0 || j >= 0; i--, j--) {
                    if (i >= 0)
                        top = AbsN.digits[i];
                    else
                        top = 0;

                    if (j >= 0)
                        bot = digits[j];
                    else
                        bot = 0;

                    int sum = top - bot;

                    if (sum < 0) {
                        borrow = 10;
                        sum = top + borrow - bot;
                        if (i != 0)
                            AbsN.digits[i-1] -= 1;
                        result += '0'+(sum);
                    }
                    else
                        result += '0'+(sum);
                }
                rSign = (sign == 1) ? 1 : -1;
                reverse(result.begin(), result.end());
                result.erase(0, result.find_first_not_of('0'));
                BigInteger r(result);
                r.sign = rSign;
                return r;
            }
        }
        BigInteger r(result);
        return r;
    }; // return the sum of this big integer object and a big integer n
    BigInteger operator -(BigInteger& n) {
        string result;
        int top, bot;
        int rSign = 1;
        BigInteger AbsCurr = *this;
        AbsCurr = Abs(AbsCurr);
        BigInteger AbsN = n;
        AbsN = Abs(AbsN);
        /*Abs to check which BigInteger is bigger than the other to determine
        which BigInteger goes to the top or bottom*/

        if (sign == n.sign) {
            if (*this == n) {
                BigInteger r("0");
                return r;
            }

            else if (AbsCurr > AbsN) {
                for (int i = AbsCurr.size() - 1, j = n.size() - 1, borrow = 0; i >= 0 || j >= 0; i--, j--) {
                    if (i >= 0)
                        top = AbsCurr.digits[i];
                    else
                        top = 0;

                    if (j >= 0)
                        bot = n.digits[j];
                    else
                        bot = 0;

                    int sum = top - bot;

                    if (sum < 0) {
                        borrow = 10;
                        sum = top + borrow - bot;
                        if (i != 0)
                            AbsCurr.digits[i-1] -= 1; //borrowing from the next digit
                        result += '0'+(sum);
                    }
                    else
                        result += '0'+(sum);
                }

                rSign = (sign == 1) ? 1 : -1;
                reverse(result.begin(), result.end());
                result.erase(0, result.find_first_not_of('0'));
                BigInteger r(result);
                r.sign = rSign;
                return r;
            }

            else if (AbsCurr < AbsN) {
                for (int i = n.size() - 1, j = length = 1, borrow = 0; i >= 0 || j >= 0; i--, j--) {
                    if (i >= 0)
                        top = n.digits[i];
                    else
                        top = 0;

                    if (j >= 0)
                        bot = digits[j];
                    else
                        bot = 0;

                    int sum = top - bot;

                    if (sum < 0) {
                        borrow = 10;
                        sum = top + borrow - bot;
                        if (i != 0)
                            n.digits[i-1] -= 1;
                        result += '0'+(sum);
                    }
                    else
                        result += '0'+(sum);
                }
                rSign *= -1;
                reverse(result.begin(), result.end());
                result.erase(0, result.find_first_not_of('0'));
                BigInteger r(result);
                r.sign = rSign;
                return r;
            }
        }

        //operator +
        else if (sign != n.sign) {
            for (int i = length - 1, j = n.size() - 1, carry = 0; i >= 0 || j >= 0 || carry; i--, j--) {
                if (i >= 0)
                    top = digits[i];
                else
                    top = 0;

                if (j >= 0)
                    bot = n.digits[j];
                else
                    bot = 0;

                int sum = top + bot + carry;

                if (sum > 9) {
                    carry = 1;
                    result += '0'+(sum%10);
                }
                else {
                    carry = 0;
                    result += '0'+(sum);
                }
            }
            rSign = (sign == 1) ? 1 : -1;
            reverse(result.begin(), result.end());
            result.erase(0, result.find_first_not_of('0'));
            BigInteger r(result);
            r.sign = rSign;
            return r;
        }
        BigInteger r(result);
        return r;
    }; // return the difference by subtracting a big integer n from this big integer object
    BigInteger operator *(int d) {

        string result;
        int rSign, top;

        if (d == 0) {
            BigInteger r("0");
            return r;
        }

        else if ((sign == 1 && d > 0) || (sign == -1 && d < 0))
            rSign = 1;

        else if ((sign == -1 && d > 0) || (sign == 1 && d < 0))
            rSign = -1;

        for (int i = length - 1, carry = 0; i >= 0 || carry; i--) {
            /*carry here acts as temporary space to store the extra digits when the
            multiplication result exceeds 10*/
            if (i >= 0)
                top = digits[i];
            else
                top = 0;

            int mult = (top * d) + carry;

            if (mult > 9) {
                carry = mult / 10;
                result += '0'+(mult%10);
            }
            else {
                carry = 0;
                result += '0'+(mult);
            }
        }

        reverse(result.begin(), result.end());
        result.erase(0, result.find_first_not_of('0'));
        BigInteger r(result);
        r.sign = rSign;
        return r;
    }; // return the multiplication of this big integer object and a single digit d (0<=d<=9)
    BigInteger operator *(BigInteger& n) {
        string addition1, addition2;
        int rSign, top;
        BigInteger r;

        if (isZero() == true || n.isZero() == true) {
            BigInteger zero("0");
            return zero;
        } //if either one of the BigInteger is 0 then the result would also be 0
        else if ((sign == 1 && n.sign == 1) || (sign == -1 && n.sign == -1))
            rSign = 1;
        else
            rSign = -1;
        //determining the sign of result

        for (int i = length - 1, carry = 0; i >= 0 || carry; i--) {
            /*carry here acts as temporary space to store the extra digits when the
            multiplication result exceeds 10*/
            if (i >= 0)
                top = digits[i];
            else
                top = 0;

            int mult = (top * n.digits[n.size()-1]) + carry;

            if (mult > 9) {
                carry = mult / 10;
                addition1 += '0'+(mult%10);
            }
            else {
                carry = 0;
                addition1 += '0'+(mult);
            }
        }
        reverse(addition1.begin(), addition1.end());

        if (n.size() == 1) {
            BigInteger res(addition1);
            res.sign = rSign;
            return res;
        }//if the multiplier is a single digit

        for (int j = n.size() - 2; j >= 0; j--) {
            for (int i = length - 1, carry = 0; i >= 0 || carry; i--) {
                if (i >= 0)
                    top = digits[i];
                else
                    top = 0;

                int mult = (top * n.digits[j]) + carry;

                if (mult > 9) {
                    carry = mult / 10;
                    addition2 += '0'+(mult%10);
                }
                else {
                    carry = 0;
                    addition2 += '0'+(mult);
                }
            }
            int zeroCount = n.size() - 1;
            while (zeroCount != j) {
                addition2.insert(addition2.begin(), '0');
                zeroCount--;
            } //adding 0 at the end of every multiplication

            reverse(addition2.begin(), addition2.end());
            BigInteger add1(addition1);
            BigInteger add2(addition2);

            if (j == n.size() - 2)
                r = add1 + add2;//first addition
            else
                r = r + add2;//addition after the first one

            addition2 = "";
        }
        r.sign = rSign;
        return r;
    }; // return the multiplication of this big object and a big integer n
    BigInteger operator /(BigInteger& n) {
        string dividen, result;
        int rSign;

        if (isZero() == true || n.isZero() == true) {
            BigInteger r("0");
            return r;
        } //if either one of the BigInteger is 0 then the result will automatically become 0
        else if ((sign == 1 && n.sign == 1) || (sign == -1 && n.sign == -1))
            rSign = 1;
        else
            rSign = -1;
        //determining the sign of result

        for (int i = 0; i < length; i++) {
            dividen += '0'+(digits[i]);
            BigInteger intDividen(dividen);

            int multiplier = 0;
            //multiplying divisor until it exceeds current dividend
            while (multiplier <= 10) {
                BigInteger divisor = n;
                divisor = Abs(divisor);
                divisor = divisor * multiplier;

                if (divisor == intDividen) {
                    BigInteger remainder;
                    remainder = intDividen - divisor;
                    dividen.erase(dividen.begin(), dividen.end());
                    result += '0'+(multiplier);
                    break;
                }

                else if (divisor > intDividen) {
                    multiplier -= 1;
                    BigInteger divisor = n;
                    divisor = Abs(divisor);
                    divisor = divisor * multiplier;
                    BigInteger remainder;
                    remainder = intDividen - divisor;
                    result += '0'+(multiplier);
                    dividen = "";

                    int j = 0;
                    int cnt = remainder.size();
                    while (cnt != 0) {
                        dividen += '0'+(remainder.digits[j]);
                        j++;
                        cnt--;
                    } //adding the remainder for the next dividend
                    break;
                }

                else
                    multiplier++;
            }
        }
        result.erase(0, result.find_first_not_of('0'));
        BigInteger r(result);
        r.sign = rSign;
        return r;
    }; // return the quotient of dividing this big integer object by a big integer n
    bool operator >(BigInteger& n) {
        if (sign == 1 && n.sign == -1)
            return true;

        else if (sign == -1 && n.sign == 1)
            return false;

        else if (sign == 1 && n.sign == 1) {
            if (length > n.length)
                return true;

            else if (length < n.length)
                return false;

            else {
                for (int i = 0; i < length; i++) {
                    if (digits[i] > n.digits[i])
                        return true;

                    else if (digits[i] < n.digits[i])
                        return false;

                    else
                        continue;
                }
                return false;
            }
        }

        else if (sign == -1 && n.sign == -1) {
            if (length < n.length)
                return true;

            else if (length > n.length)
                return false;

            else {
                for (int i = 0; i < length; i++) {
                    if (digits[i] < n.digits[i])
                        return true;

                    else if (digits[i] > n.digits[i])
                        return false;

                    else
                        continue;
                }
                return false;
            }
        }
        return true;
    }; // check if this big integer object is larger than the big integer n
    bool operator <(BigInteger& n) {
        if (sign == 1 && n.sign == -1)
            return false;

        else if (sign == -1 && n.sign == 1)
            return true;

        else if (sign == 1 && n.sign == 1) {
            if (length > n.length)
                return false;

            else if (length < n.length)
                return true;

            else {
                for (int i = 0; i < length; i++) {
                    if (digits[i] > n.digits[i])
                        return false;

                    else if (digits[i] < n.digits[i])
                        return true;

                    else
                        continue;
                }
                return true;
            }
        }

        else if (sign == -1 && n.sign == -1) {
            if (length < n.length)
                return false;

            else if (length > n.length)
                return true;

            else {
                for (int i = 0; i < length; i++) {
                    if (digits[i] < n.digits[i])
                        return false;

                    else if (digits[i] > n.digits[i])
                        return true;

                    else
                        continue;
                }
                return false;
            }
        }
        return true;
    }; // check if this big integer object is smaller than the big integer n
    bool operator ==(BigInteger& n) {
        if (length == n.size()) {
            for (int i = 0; i < length; i++) {
                if (digits[i] != n.digits[i])
                    return false;

                else
                    continue;
            }
            return true;
        }

        else
            return false;
    }; // check if this big integer object is equal to the big integer n
    bool operator >=(BigInteger& n) {
        if (*this > n)
            return true;

        else if (*this == n)
            return true;

        else
            return false;
    }; // check if this big integer object is larger than or equal to the big integer n

    friend BigInteger Abs(BigInteger& n) {
        if (n.sign == -1)
            n.sign = 1;
        return n;
    }; // a friend function returning the absolute value of the big number n
    friend ostream& operator<<(ostream& output, BigInteger& n) {
        if (n.sign == -1)
            output << "-";

        for (int i = 0; i < n.length; i++) {
            output << n.digits[i];
        }

        return output;
    }; // overloading the insertion operator for outputting a big number

private:
    int length; // length of the big integer
    int* digits; // an array storing the digits of the big integer
    int sign; // the sign of the big integer
};

int main() {
    /*BigInteger n1("1878365515132515443215132"), n2("25521523312");
    BigInteger n3("-123456789987654321"), n4("-123456789987654321");

    BigInteger n, t1, t2, t3, t4, t5, t6, t7;
    cout << n2.size() << endl;
    cout << (t2 == n1) << endl;

    cout << "n1 : " << n1 << endl;
    cout << "n2 : " << n2 << endl;


    t1 = n1 + n2;
    cout << "n1 + n2 = " << t1 << endl;

    t2 = n1 - n2;
    cout << "n1 - n2 = " << t2 << endl;

    t3 = n1 * 4;
    cout << "n1 * 4 = " << t3 << endl;

    t4 = n1 * n2;
    cout << "n1 * n2 = " << t4 << endl;

    t5 = n1 / n2;
    cout << "n1 / n2 = " << t5 << endl;

    cout << ">= " << (n3 >= n4) << endl;

    cout << "== " << (n3 == n4) << endl;

    cout << ">  " << (n3 > n1) << endl;

    cout << "<  " << (n3 < n2) << endl;*/

    /*BigInteger n1("-9999888852245546546365637657476365463665465"), n2("3045452545446132155444422321");
    BigInteger n3("-123456789987654321"), n4("-123456789987654321");

    BigInteger n, t1, t2, t3, t4, t5, t6, t7;
    cout << n2.size() << endl;
    cout << (t2 == n1) << endl;
    t1 = n1 / n2;
    t2 = n1 - n2;
    t3 = n1 + n2;
    t4 = n1 * n2;
    t5 = n1 * 3;
    t6 = n3 + n4;
    t7 = n3 - n4;
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;
    cout << t4 << endl;
    cout << t5 << endl;
    cout << t6 << endl;
    cout << t7 << endl;
    cout << (n3 >= n4) << endl;
    cout << (n3 == n4) << endl;
    cout << (n3 > n1) << endl;
    cout << (n3 < n2) << endl;*/

    BigInteger n1("29999666556736639639096912972429096390996395000000000000000000000000000"), n2("454520402512961023305234815420040291802134001111722441533522122844265");
    BigInteger n;
    n = n2 + n1;
    cout << n << endl;
}
