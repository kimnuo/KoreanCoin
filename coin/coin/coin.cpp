// 주화 판별 프로그램

//변수 mgnt은 magnetic, 동전의 자성을 뜻합니다.
//구조체 insCns 은 Inserted Coin, 넣어진 동전을 뜻합니다.
//함수gtvI는  Get Value By Index, 요소에 값을 입력 받고 되돌려주는 함수를 뜻합니다.
//Error1은 규격 미도달, Error02는 국내주화가 아닌경우 발생합니다
//mrgEr_pN와 moe 는 margin of error로 오차범위를 뜻합니다.

#include <iostream>
#include <cmath>
using namespace std;

class Coin {
protected:
	int p[8], mgnt;

public:
	Coin(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int mgnt) :
		mgnt(mgnt) {
		p[0] = p0;
		p[1] = p1;
		p[2] = p2;
		p[3] = p3;
		p[4] = p4;
		p[5] = p5;
		p[6] = p6;
		p[7] = p7;
	}

	int getP(int idx) const {
		return p[idx];
	}

	virtual int getMgnt() const {
		return mgnt;
	}

	virtual void printCoinInfo() const {
		cout << "동전 정보:" << endl;
		for (int i = 0; i < 8; i++) {
			cout << "P" << i << ":" << p[i] << " ";
		}
		cout << "\n자성: " << mgnt << endl;
	}

	virtual int getMrgErP(int idx) const {
		return 0;
	}
};

class Coin10 : public Coin {
private:
	int mrgEr_p[8];

public:
	Coin10() : Coin(127, 107, 94, 55, 46, 58, 111, 86, 0) {
		mrgEr_p[0] = abs(2);
		mrgEr_p[1] = abs(2);
		mrgEr_p[2] = abs(1);
		mrgEr_p[3] = abs(4);
		mrgEr_p[4] = abs(2);
		mrgEr_p[5] = abs(2);
		mrgEr_p[6] = abs(1);
		mrgEr_p[7] = abs(2);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class Coin50 : public Coin {
private:
	int mrgEr_p[8];

public:
	Coin50() : Coin(116, 116, 88, 56, 35, 66, 103, 89, 0) {
		mrgEr_p[0] = abs(3);
		mrgEr_p[1] = abs(3);
		mrgEr_p[2] = abs(3);
		mrgEr_p[3] = abs(3);
		mrgEr_p[4] = abs(3);
		mrgEr_p[5] = abs(2);
		mrgEr_p[6] = abs(2);
		mrgEr_p[7] = abs(2);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class Coin100 : public Coin {
private:
	int mrgEr_p[8];

public:
	Coin100() : Coin(110, 167, 97, 77, 29, 116, 99, 120, 0) {
		mrgEr_p[0] = abs(3);
		mrgEr_p[1] = abs(2);
		mrgEr_p[2] = abs(3);
		mrgEr_p[3] = abs(14);
		mrgEr_p[4] = abs(3);
		mrgEr_p[5] = abs(3);
		mrgEr_p[6] = abs(2);
		mrgEr_p[7] = abs(2);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class Coin500 : public Coin {
private:
	int mrgEr_p[8];

public:
	Coin500() : Coin(122, 190, 118, 133, 40, 140, 108, 144, 0) {
		mrgEr_p[0] = abs(2);
		mrgEr_p[1] = abs(2);
		mrgEr_p[2] = abs(4);
		mrgEr_p[3] = abs(10);
		mrgEr_p[4] = abs(3);
		mrgEr_p[5] = abs(2);
		mrgEr_p[6] = abs(2);
		mrgEr_p[7] = abs(2);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class InsCns : public Coin {
public:
	InsCns() : Coin(0, 0, 0, 0, 0, 0, 0, 0, 0) {
		cout << "자성 : ";
		cin >> mgnt;
		if (mgnt > 0) {
			cout << "Error02\n";
		}
		else {
			for (int i = 0; i < 8; i++) {
				cout << "p" << i << " : ";
				gtvI(i);
			}
		}
	}

private:
	void gtvI(int idx) {
		cin >> p[idx];
	}
};

bool compareCoins(const InsCns& insertedCoin, const Coin& standardCoin) {
	int moeP = 0;
	int moeM = abs(insertedCoin.getMgnt() - standardCoin.getMgnt()); // M 값 오차 계산
	for (int i = 0; i < 8; ++i) {
		moeP = abs(insertedCoin.getP(i) - standardCoin.getP(i));
		cout << i << "번P " << moeP << ", " << endl;
		if (moeP >= standardCoin.getMrgErP(i) || moeM >= standardCoin.getMrgErP(i)) {
			return false;
		}
	}
	return true;
}

int main() {
	Coin10 coin10;
	Coin50 coin50;
	Coin100 coin100;
	Coin500 coin500;
	int cnt10 = 0, cnt50 = 0, cnt100 = 0, cnt500 = 0, mNum = 0, price=0, total;
	total = (cnt10*10) + (cnt50*50) + (cnt100*100) + (cnt500*500);

	cout << "메뉴를 선택 해주세요" << "\n1.일회용 승차권 2.우대용 3.교통카드 충전" << "\n-----------------------------------------" << endl;
	cin >> mNum;
	switch (mNum)
	{
	case 1:
		cout << "1,800원 입니다. 동전을 투입해주세요"<<endl;
		break;
	case 2:
		cout << "100원 입니다. 동전을 투입해주세요"<< endl;
		break;
	case 3:
		cout << "충전 할 금액을 입력해주세요." << endl;
		cin >> price;
		cout <<"충전 할 금액은 "<<price<<"원 입니다."<<"동전을 투입해주세요" << endl;
		break;
	default:
		break;
	}

	while (true) // 주화 판별 함수를 호출하여 유효하지 동전으로 판별 되었을 경우, (추후 목표값 달성시까지)동전 반환 및 프로그램 종료
	{
	
		cout << "동전을 투입하세요" << endl;
		InsCns insCns;
		insCns.printCoinInfo();
		if (compareCoins(insCns, coin10)) {
			cnt10++;
			cout << "10원, count" << cnt10 << "개" << endl;
			cout << "현재 투입금액 : " << total;
		}
		else if (compareCoins(insCns, coin50)) {
			cnt50++;
			cout << "50원, count" << cnt50 << "개" << endl;
			cout << "현재 투입금액 : " << total;
		}
		else if (compareCoins(insCns, coin100)) {
			cnt100++;
			cout << "100원, count" << cnt100 << "개" << endl;
			cout << "현재 투입금액 : " << total;
		}
		else if (compareCoins(insCns, coin500)) {
			cnt500++;
			cout << "500원, count" << cnt500 << "개" << endl;
			cout << "현재 투입금액 : " << total;
		}
		else {
			cout << "동전이 반환되었습니다."<<endl;
		}
	}

	return 0;
}

