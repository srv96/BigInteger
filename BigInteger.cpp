#include<iostream>

#include<fstream>

using namespace std;
class BigInteger {
    private: char sign;
    int size;
    string info;
    int * num;
    friend int * sum(int * , int, int * , int);
    friend int * difference(int * , int, int * , int);
    friend int * multipication(int * , int, int * , int);
    string getFileData(string fileName);
    bool isNumber(string number);
    public: BigInteger();
    BigInteger(const char * str);
    BigInteger(string);
    BigInteger(long long int number);
    void show();
    friend istream & operator >> (istream & , BigInteger & );
    friend ostream & operator << (ostream & , BigInteger & );
    void operator = (BigInteger);
    void operator = (int);
    void operator = (string);
    void operator = (const char * );
    void operator++();
    void operator--();
    void operator - ();
    friend BigInteger operator + (BigInteger, BigInteger);
    friend BigInteger operator + (BigInteger, int);
    friend BigInteger operator + (int, BigInteger);
    void operator += (BigInteger);
    void operator += (int);
    friend BigInteger operator - (BigInteger, BigInteger);
    friend BigInteger operator - (BigInteger, int);
    friend BigInteger operator - (int, BigInteger);
    void operator -= (BigInteger);
    void operator -= (int);
    friend BigInteger operator * (BigInteger, BigInteger);
    friend BigInteger operator * (BigInteger, int);
    friend BigInteger operator * (int, BigInteger);
    void operator *= (BigInteger);
    void operator *= (int);
    friend bool operator > (BigInteger, BigInteger);
    friend bool operator > (BigInteger, int);
    friend bool operator > (int, BigInteger);
    friend bool operator >= (BigInteger, BigInteger);
    friend bool operator >= (BigInteger, int);
    friend bool operator >= (int, BigInteger);
    friend bool operator < (BigInteger, BigInteger);
    friend bool operator < (BigInteger, int);
    friend bool operator < (int, BigInteger);
    friend bool operator <= (BigInteger, BigInteger);
    friend bool operator <= (BigInteger, int);
    friend bool operator <= (int, BigInteger);
    friend bool operator == (BigInteger, BigInteger);
    friend bool operator == (BigInteger, int);
    friend bool operator == (int, BigInteger);
    friend bool operator != (BigInteger, BigInteger);
    friend bool operator != (BigInteger, int);
    friend bool operator != (int, BigInteger);
};
void BigInteger::show() {
    cout << "sign = " << sign << endl;
    cout << "size = " << size << endl;
    cout << "info = " << info << endl;
    cout << "info size : " << info.size() << endl;
    cout << "num = ";
    for (int i = 0; i < size; i++) cout << num[i];
    cout << endl;
}
BigInteger::BigInteger() {
    sign = '+'; //do proper initialisation
    size = 0;
    info = "";
    num = new int[1];
    num[0] = 0;
}
BigInteger::BigInteger(const char * numstr) {
    string number = numstr;
    if (isNumber(number)) {
        sign = (number[0] == '+' || number[0] == '-') ? number[0] : '+';
        size = (number[0] == '+' || number[0] == '-') ? number.size() - 1 : number.size();
        num = new int[size];
        info = "";
        if (number[0] == '+' || number[0] == '-')
            for (int i = 1; i < size + 1; i++) {
                info += number[i];
                num[i - 1] = number[i] - 48;
            }
        else {
            for (int i = 0; i < size; i++) {
                info += number[i];
                num[i] = number[i] - 48;
            }

        }
    } else {
        string fileData = getFileData(number);
        if (isNumber(fileData)) {
            sign = (fileData[0] == '+' || fileData[0] == '-') ? fileData[0] : '+';
            size = (fileData[0] == '+' || fileData[0] == '-') ? fileData.size() - 1 : fileData.size();
            num = new int[size];
            info = "";
            if (fileData[0] == '+' || fileData[0] == '-')
                for (int i = 1; i < size + 1; i++) {
                    info += fileData[i];
                    num[i - 1] = fileData[i] - 48;
                }
            else {
                for (int i = 0; i < size; i++) {
                    info += fileData[i];
                    num[i] = fileData[i] - 48;
                }
            }
        } else {
            sign = '+';
            size = 1;
            info = "0";
            num = new int[1];
            num[0] = 0;
        }
    }
}
BigInteger::BigInteger(string number) {
    if (isNumber(number)) {
        sign = (number[0] == '+' || number[0] == '-') ? number[0] : '+';
        size = (number[0] == '+' || number[0] == '-') ? number.size() - 1 : number.size();
        num = new int[size];
        if (number[0] == '+' || number[0] == '-')
            for (int i = 1; i < size + 1; i++) {
                info += number[i];
                num[i - 1] = number[i] - 48;
            }
        else {
            for (int i = 0; i < size; i++) {
                info += number[i];
                num[i] = number[i] - 48;
            }
        }
    } else {
        string fileData = getFileData(number);
        if (isNumber(fileData)) {
            sign = (fileData[0] == '+' || fileData[0] == '-') ? fileData[0] : '+';
            size = (fileData[0] == '+' || fileData[0] == '-') ? fileData.size() - 1 : fileData.size();
            num = new int[size];
            if (fileData[0] == '+' || fileData[0] == '-')
                for (int i = 1; i < size + 1; i++) {
                    info += fileData[i];
                    num[i - 1] = fileData[i] - 48;
                }
            else {
                for (int i = 0; i < size; i++) {
                    info += fileData[i];
                    num[i] = fileData[i] - 48;
                }
            }
        } else {
            sign = '+';
            size = 1;
            info = "0";
            num = new int[1];
            num[0] = 0;
        }
    }
}
BigInteger::BigInteger(long long int number) {
    size = 0;
    info = "";
    for (long long int temp = number; temp != 0; temp /= 10) size++;
    sign = (number >= 0) ? '+' : '-';
    for (int i = size - 1; i >= 0; i--) {
        num[i] = number % 10;
        number /= 10;
    }
    for (int i = 0; i < size; i++) info += num[i] + 48;
}
int * sum(int * arr1, int size1, int * arr2, int size2) {
    int size = (size1 >= size2) ? size1 + 1 : size2 + 1;
    int * arr = new int[size];
    int t, t1 = size1 - 1, t2 = size2 - 1;
    for (t = size - 1; t1 >= 0 && t2 >= 0; t--)
        arr[t] = arr1[t1--] + arr2[t2--];
    if (size1 > size2)
        while (t1 >= 0) arr[t--] = arr1[t1--];
    else
        while (t2 >= 0) arr[t--] = arr2[t2--];
    for (int i = size - 1; i > 0; i--) {
        arr[i - 1] += arr[i] / 10;
        arr[i] %= 10;
    }
    return arr;
}
int * difference(int * temp1, int size1, int * temp2, int size2) {
    int * big = new int[size1];
    int * small = new int[size1];
    int * result = new int[size1];
    for (int i = 0; i < size1; i++) big[i] = temp1[i];
    for (int i = 0; i < size1; i++) small[i] = 0;
    int k = size2 - 1;
    for (int i = size1 - 1; k >= 0; i--) small[i] = temp2[k--];
    for (int i = size1 - 1; i >= 0; i--) {
        if (big[i] < small[i]) {
            big[i - 1]--;
            big[i] += 10;
            result[i] = big[i] - small[i];
            continue;
        }
        result[i] = big[i] - small[i];

    }
    return result;

}
int * multipication(int * num1, int size1, int * num2, int size2) {
    int size = size1 + size2;
    int * result0 = new int[size];
    int * result1 = new int[size];
    for (int i = 0; i < size; i++) {
        result0[i] = 0;
        result1[i] = 0;
    }
    int k = size - 1, l = size - 1;
    for (int j = size2 - 1; j >= 0; j--) {
        k = l--;
        for (int i = size1 - 1; i >= 0; i--, k--) result1[k] = num2[j] * num1[i];
        for (int i = size - 1; i >= 0; i--) {
            result1[i - 1] += result1[i] / 10;
            result1[i] %= 10;
        }
        for (int i = 0; i < size; i++) result0[i] += result1[i];
        for (int i = size - 1; i >= 0; i--) {
            result0[i - 1] += result0[i] / 10;
            result0[i] %= 10;
        }
        for (int i = 0; i < size; i++) result1[i] = 0;
    }
    return result0;
}
string BigInteger::getFileData(string fileName) {
    ifstream fin;
    fin.open(fileName.c_str(), ios::in);
    string buffer;
    fin >> buffer;
    fin.close();
    return buffer;
}
bool BigInteger::isNumber(string number) {
    bool flag = true;
    for (int i = 0; i < number.size(); i++) {
        if (((i == 0) && ((number[i] == '+' || number[i] == '-') || (number[i] >= 48 && number[i] <= 57))) || ((i != 0) && (number[i] >= 48 && number[i] <= 57))) continue;
        else {
            flag = false;
            break;
        }
    }
    return flag;
}
void BigInteger::operator = (BigInteger B) { //assignment of a BigInteger into another
    sign = B.sign;
    size = 0;
    info = "";
    size = B.size;
    num = new int[size];
    for (int i = 0; i < size; i++) num[i] = B.num[i];
    for (int i = 0; i < size; i++) info += B.info[i];
}
void BigInteger::operator = (int number) { //assignment of a small number to a BigInteger
    int temp = number;
    int digit = 0;
    while (temp != 0) {
        digit++;
        temp /= 10;
    }
    temp = number;
    sign = (number > 0 || number == 0) ? '+' : '-';
    if (temp < 0) temp *= -1;
    size = digit;
    num = new int[size];
    for (int i = digit - 1; i >= 0; i--) {
        num[i] = temp % 10;
        temp /= 10;
    }
    for (int i = 0; i < digit; i++) info += num[i] + 48;
}
void BigInteger::operator = (string number) { //assignment of a large number into BigInteger
    if (isNumber(number)) {
        sign = (number[0] == '+' || number[0] == '-') ? number[0] : '+';
        size = (number[0] == '+' || number[0] == '-') ? number.size() - 1 : number.size();
        num = new int[size];
        if (number[0] == '+' || number[0] == '-')
            for (int i = 1; i < size + 1; i++) {
                info += number[i];
                num[i - 1] = number[i] - 48;
            }
        else {
            for (int i = 0; i < size; i++) {
                info += number[i];
                num[i] = number[i] - 48;
            }
        }
    } else {
        string fileData = getFileData(number);
        if (isNumber(fileData)) {
            sign = (fileData[0] == '+' || fileData[0] == '-') ? fileData[0] : '+';
            size = (fileData[0] == '+' || fileData[0] == '-') ? fileData.size() - 1 : fileData.size();
            num = new int[size];
            if (fileData[0] == '+' || fileData[0] == '-')
                for (int i = 1; i < size + 1; i++) {
                    info += fileData[i];
                    num[i - 1] = fileData[i] - 48;
                }
            else {
                for (int i = 0; i < size; i++) {
                    info += fileData[i];
                    num[i] = fileData[i] - 48;
                }
            }
        } else {
            sign = '+';
            size = 1;
            info = "0";
            num = new int[1];
            num[0] = 0;
        }
    }
}
void BigInteger::operator = (const char * numstr) { //assignment of a large number into BigInteger
    string number = numstr;
    if (isNumber(number)) {
        sign = (number[0] == '+' || number[0] == '-') ? number[0] : '+';
        size = (number[0] == '+' || number[0] == '-') ? number.size() - 1 : number.size();
        num = new int[size];
        info = "";
        if (number[0] == '+' || number[0] == '-')
            for (int i = 1; i < size + 1; i++) {
                info += number[i];
                num[i - 1] = number[i] - 48;
            }
        else {
            for (int i = 0; i < size; i++) {
                info += number[i];
                num[i] = number[i] - 48;
            }

        }
    } else {
        string fileData = getFileData(number);
        if (isNumber(fileData)) {
            sign = (fileData[0] == '+' || fileData[0] == '-') ? fileData[0] : '+';
            size = (fileData[0] == '+' || fileData[0] == '-') ? fileData.size() - 1 : fileData.size();
            num = new int[size];
            info = "";
            if (fileData[0] == '+' || fileData[0] == '-')
                for (int i = 1; i < size + 1; i++) {
                    info += fileData[i];
                    num[i - 1] = fileData[i] - 48;
                }
            else {
                for (int i = 0; i < size; i++) {
                    info += fileData[i];
                    num[i] = fileData[i] - 48;
                }
            }
        } else {
            sign = '+';
            size = 1;
            info = "0";
            num = new int[1];
            num[0] = 0;
        }
    }
}
void BigInteger::operator - () {
    sign = (sign == '+') ? '-' : '+';
}
void BigInteger::operator++() {
    BigInteger temp, inc;
    inc = 1;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp + inc;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
void BigInteger::operator += (BigInteger A) {
    BigInteger temp;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp + A;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
void BigInteger::operator += (int n) {
    BigInteger temp, inc;
    inc = n;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp + inc;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
void BigInteger::operator--() {
    BigInteger temp, inc;
    inc = 1;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp - inc;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
void BigInteger::operator -= (BigInteger A) {
    BigInteger temp;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp - A;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
void BigInteger::operator -= (int n) {
    BigInteger temp, dec;
    dec = n;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp - dec;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
BigInteger operator + (BigInteger A, BigInteger B) {
    BigInteger result;
    if (A.sign == B.sign) {
        result.sign = A.sign;
        result.num = sum(A.num, A.size, B.num, B.size);
        result.size = (A > B) ? A.size + 1 : B.size + 1;
        if (result.num[0] == 0 && result.size != 1) {
            result.size--;
            for (int i = 0; i < result.size; i++) result.num[i] = result.num[i + 1];
        }
    } else {
        BigInteger C, D;
        C = A;
        D = B;
        C.sign = '+';
        D.sign = '+';
        result.sign = (C > D) ? A.sign : B.sign;
        result.num = difference((C > D) ? C.num : D.num, (C > D) ? C.size : D.size, (C < D) ? C.num : D.num, (C < D) ? C.size : D.size);
        result.size = (C > D) ? C.size : D.size;
        while (result.num[0] == 0 && result.size != 1) {
            result.size--;
            for (int i = 0; i < result.size; i++) result.num[i] = result.num[i + 1];
        }
    }
    for (int i = 0; i < result.size; i++) result.info += result.num[i] + 48;
    return result;
}
BigInteger operator + (BigInteger A, int number) { //add a BigInteger with primitive
    BigInteger B, temp;
    B = number;
    temp = A + B;
    return temp;
}
BigInteger operator + (int number, BigInteger A) { //add a primitive integer with
    BigInteger B, temp;
    B = number;
    temp = A + B;
    return temp;
}
BigInteger operator - (BigInteger A, BigInteger B) {
    BigInteger result;
    if (A.sign == B.sign) {
        BigInteger C, D;
        C = A;
        D = B;
        C.sign = '+';
        D.sign = '+';
        result.sign = (A < B) ? '-' : '+';
        result.num = difference((C > D) ? C.num : D.num, (C > D) ? C.size : D.size, (C < D) ? C.num : D.num, (C < D) ? C.size : D.size);
        result.size = (C > D) ? A.size : B.size;
        while (result.num[0] == 0 && result.size != 1) {
            result.size--;
            for (int i = 0; i < result.size; i++) result.num[i] = result.num[i + 1];
        }
    } else {
        result.sign = A.sign;
        BigInteger C, D;
        C = A;
        D = B;
        C.sign = '+';
        D.sign = '+';
        result.num = sum((C > D) ? C.num : D.num, (C > D) ? C.size : D.size, (C < D) ? C.num : D.num, (C < D) ? C.size : D.size);
        result.size = (C > D) ? C.size + 1 : D.size + 1;
        while (result.num[0] == 0 && result.size != 1) {
            result.size--;
            for (int i = 0; i < result.size; i++) result.num[i] = result.num[i + 1];
        }
    }
    for (int i = 0; i < result.size; i++) result.info += result.num[i] + 48;
    return result;
}
BigInteger operator - (BigInteger A, int number) { //substract a BigInteger with primitive
    BigInteger B, temp;
    B = number;
    temp = A - B;
    return temp;
}
BigInteger operator - (int number, BigInteger A) { //substract a primitive integer with
    BigInteger B, temp;
    B = number;
    temp = A - B;
    return temp;
}
BigInteger operator * (BigInteger A, BigInteger B) {
    BigInteger result;
    result.sign = (A.sign == B.sign) ? '+' : '-';
    result.size = A.size + B.size;
    result.num = multipication(A.num, A.size, B.num, B.size);
    while (result.num[0] == 0 && result.size != 1) {
        result.size--;
        for (int i = 0; i < result.size; i++) result.num[i] = result.num[i + 1];
    }
    for (int i = 0; i < result.size; i++) result.info += result.num[i] + 48;
    return result;
}
BigInteger operator * (BigInteger A, int number) { //substract a BigInteger with primitive
    BigInteger B, temp;
    B = number;
    temp = A * B;
    return temp;
}
BigInteger operator * (int number, BigInteger A) { //substract a primitive integer with
    BigInteger B, temp;
    B = number;
    temp = A * B;
    return temp;
}
void BigInteger::operator *= (BigInteger A) {
    BigInteger temp;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp * A;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
void BigInteger::operator *= (int n) {
    BigInteger temp, inc;
    inc = n;
    temp.sign = this -> sign;
    temp.size = this -> size;
    temp.num = this -> num;
    temp.info = this -> info;
    temp = temp * inc;
    this -> sign = temp.sign;
    this -> size = temp.size;
    this -> num = temp.num;
    this -> info = temp.info;
}
bool operator > (BigInteger A, BigInteger B) {
    bool flag;
    if (A.sign == '-' && B.sign == '-') {
        BigInteger C, D;
        C = A;
        D = B;
        C.sign = '+';
        D.sign = '+';
        if (C < D) return true;
        else return false;
    } else if (A.sign != B.sign) {
        if (A.sign == '+') return true;
        else return false;
    }
    if (A.size > B.size) return true;
    else if (B.size > A.size) return false;
    else {
        int count = 0;
        for (int i = 0; i < A.size; i++) {
            if (A.num[i] > B.num[i]) {
                flag = true;
                break;
            } else if (B.num[i] > A.num[i]) {
                flag = false;
                break;
            } else {
                count++;
                continue;
            }
        }
        if (count == A.size) return false;
        else return flag;
    }
}
bool operator > (BigInteger A, int num) {
    BigInteger B;
    B = num;
    return (A > B);
}
bool operator > (int num, BigInteger B) {
    BigInteger A;
    A = num;
    return (A > B);
}
bool operator >= (BigInteger A, BigInteger B) {
    return (A > B || A == B);
}
bool operator >= (BigInteger A, int num) {
    BigInteger B;
    B = num;
    return (A >= B);
}
bool operator >= (int num, BigInteger B) {
    BigInteger A;
    A = num;
    return (A >= B);
}
bool operator < (BigInteger A, BigInteger B) { //for checking which BigInteger is smaller
    if (A.sign == '-' && B.sign == '-') {
        BigInteger C, D;
        C = A;
        D = B;
        C.sign = '+';
        D.sign = '+';
        if (C > D) return true;
        else return false;
    } else if (A.sign != B.sign) {
        if (A.sign == '-') return true;
        else return false;
    }
    if (A.size < B.size) return true;
    else if (B.size < A.size) return false;
    else {
        bool flag;
        int count = 0;
        for (int i = 0; i < A.size; i++) {
            if (A.num[i] < B.num[i]) {
                flag = true;
                break;
            } else if (B.num[i] < A.num[i]) {
                flag = false;
                break;
            } else {
                count++;
                continue;
            }
        }
        if (count == A.size) return false;
        else return flag;
    }
}
bool operator < (BigInteger A, int num) {
    BigInteger B;
    B = num;
    return (A < B);
}
bool operator < (int num, BigInteger B) {
    BigInteger A;
    A = num;
    return (A < B);
}
bool operator <= (BigInteger A, BigInteger B) {
    return (A < B || A == B);
}
bool operator <= (BigInteger A, int num) {
    BigInteger B;
    B = num;
    return (A <= B);
}
bool operator <= (int num, BigInteger B) {
    BigInteger A;
    A = num;
    return (A <= B);
}
bool operator == (BigInteger A, BigInteger B) {
    if (A.sign != B.sign) return false;
    else if (A.info.size() != B.info.size()) return false;
    else {
        int size = A.info.size();
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (A.info[i] == B.info[i]) count++;
            else break;
        }
        if (count == size) return true;
        else return false;
    }
}
bool operator == (BigInteger A, int num) {
    BigInteger B;
    B = num;
    return (A == B);
}
bool operator == (int num, BigInteger B) {
    BigInteger A;
    A = num;
    return (A == B);
}
bool operator != (BigInteger A, BigInteger B) {
    if (A.info.size() != B.info.size()) return true;
    else {
        int size = A.info.size();
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (A.info[i] == B.info[i]) count++;
            else break;
        }
        if (count == size) {
            if (A.sign == B.sign) return false;
            else return true;
        } else return false;
    }
}
bool operator != (BigInteger A, int num) {
    BigInteger B;
    B = num;
    return (A != B);
}
bool operator != (int num, BigInteger B) {
    BigInteger A;
    A = num;
    return (A != B);
}
istream & operator >> (istream & din, BigInteger & B) { //accept a BigInteger like normal
    cin >> B.info;
    if (B.info[0] == '+' || B.info[0] == '-') {
        B.size = B.info.size() - 1;
        B.sign = B.info[0];
        for (int i = 0; i < B.size; i++) B.info[i] = B.info[i + 1];
        B.info[B.size] = '\0';
    } else {
        B.sign = '+';
        B.size = B.info.size();
    } //primitive data type
    B.num = new int[B.size];
    for (int i = 0; i < B.size; i++) B.num[i] = B.info[i] - 48;
    return din;
}
ostream & operator << (ostream & dout, BigInteger & B) {
    if (B.sign == '-' && B.num[0] != 0) cout << B.sign; //display BigInteger like normal
    cout << B.info; //primitive data type
    return dout;
}
int main() {
    BigInteger a = "123", b = "123", c;
    a.show();
    b.show();
    c = a + b;
    c.show();
}