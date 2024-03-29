﻿// 주화 판별 프로그램

//변수 mgnt은 magnetic, 동전의 자성을 뜻합니다.
//구조체 insCns 은 Inserted Coin, 넣어진 동전을 뜻합니다.
//함수gtvI는  Get Value By Index, 요소에 값을 입력 받고 되돌려주는 함수를 뜻합니다.
//Error1은 규격 미도달, Error02는 국내주화가 아닌경우 발생합니다.
//mrgEr_pN와 moe 는 margin of error로 오차범위를 뜻합니다.
//tPrice는 Ticket Price로 티켓의 가격입니다.
//tType은 Ticket Type로 1~3까지 있으며 1은 일회용 승차권 2는 우대권 3은 교통카드 충전입니다.
//OTicket은 One Time Ticket으로 일회용 승차권입니다.
//gttp은 Get Ticket Price로 승차권의 가격을 입력받습니다.
//slcTicket은 selected Ticket으로 선택된 승차권 종류를 뜻합니다.

#include "iostream"
#include "cmath"
using namespace std;

class Coin { //Coin 클래스 각 권종의 속성을 선언
protected:
	int p[8], mgnt; //P값과 자성값 변수를 protected로 선언

public:
	Coin(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int mgnt) : //동전의 P값 생성자
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

	int getP(int idx) const { //각 동전의 P값을 반환
		return p[idx];
	}

	virtual int getMgnt() const { //각 동전의 자성값을 반환
		return mgnt;
	}

	virtual int getMrgErP(int idx) const { //각 동전의 오차값을 반환
		return 0;
	}
};

class Coin10 : public Coin { //10원 클래스
private:
	int mrgEr_p[8];

public:
	Coin10() : Coin(128, 107, 94, 56, 47, 57, 111, 86, 0) {
		mrgEr_p[0] = abs(3);
		mrgEr_p[1] = abs(3);
		mrgEr_p[2] = abs(2);
		mrgEr_p[3] = abs(5);
		mrgEr_p[4] = abs(3);
		mrgEr_p[5] = abs(3);
		mrgEr_p[6] = abs(2);
		mrgEr_p[7] = abs(3);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class Coin50 : public Coin { //50원 클래스
private:
	int mrgEr_p[8];

public:
	Coin50() : Coin(116, 116, 88, 57, 36, 66, 104, 90, 0) {
		mrgEr_p[0] = abs(4);
		mrgEr_p[1] = abs(5);
		mrgEr_p[2] = abs(3);
		mrgEr_p[3] = abs(3);
		mrgEr_p[4] = abs(4);
		mrgEr_p[5] = abs(5);
		mrgEr_p[6] = abs(3);
		mrgEr_p[7] = abs(2);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class Coin100 : public Coin { //100원 클래스
private:
	int mrgEr_p[8];

public:
	Coin100() : Coin(111, 167, 97, 78, 30, 116, 100, 121, 0) {
		mrgEr_p[0] = abs(3);
		mrgEr_p[1] = abs(8);
		mrgEr_p[2] = abs(3);
		mrgEr_p[3] = abs(20);
		mrgEr_p[4] = abs(3);
		mrgEr_p[5] = abs(6);
		mrgEr_p[6] = abs(2);
		mrgEr_p[7] = abs(4);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class Coin500 : public Coin { //500원 클래스
private:
	int mrgEr_p[8];

public:
	Coin500() : Coin(123, 190, 119, 134, 41, 140, 109, 145, 0) {
		mrgEr_p[0] = abs(2);
		mrgEr_p[1] = abs(2);
		mrgEr_p[2] = abs(4);
		mrgEr_p[3] = abs(20);
		mrgEr_p[4] = abs(4);
		mrgEr_p[5] = abs(3);
		mrgEr_p[6] = abs(3);
		mrgEr_p[7] = abs(3);
	}

	int getMrgErP(int idx) const override {
		return mrgEr_p[idx];
	}
};

class InsCns : public Coin {//동전의 P값과 자성을 입력 받을 클래스
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

class Ticket // 승차권 클래스
{
protected:
	int tPrice, tType, targetAmount;

public:
	Ticket(int tType) : tType(tType)
	{
	}
	int getTargetAmount() const
	{
		return targetAmount;
	}
};

class OTicket : public Ticket
{
public:
	OTicket() : Ticket(1)
	{
		cout << "일회용 승차권 발매중입니다." << endl;
		cout << "승차권의 금액을 입력해주세요: ";
		gttp();
		targetAmount = tPrice;
	}
	int getTargetAmount() const
	{
		return targetAmount;
	}
private:
	void gttp()
	{
		cin >> tPrice;
	}
};

class PreTicket : public Ticket
{
public:
	PreTicket() : Ticket(2)
	{
		tPrice = 500;
		cout << "우대승차권 발매중입니다." << endl;
		cout << "신분증을 인식기에 인식시켜주세요\n" << endl;
		targetAmount = tPrice;
	}
	int getTargetAmount() const
	{
		return targetAmount;
	}
};

class ChargeTicket : public Ticket
{
public:
	ChargeTicket() : Ticket(3)
	{
		cout << "교통카드 충전중입니다." << endl;
		cout << "충전하실 금액을 입력해주세요";
		gttp();
		cout << "교통카드를 올려주세요\n"<<endl;
		targetAmount = tPrice;
	}
	int getTargetAmount() const
	{
		return targetAmount;
	}
private:
	void gttp()
	{
		cin >> tPrice;
	}
};


bool compareCoins(const InsCns& insertedCoin, const Coin& standardCoin) {
	int moe = 0; //각 항목과 비교할 오차범위
	for (int i = 0; i < 8; ++i) {
		moe = abs(insertedCoin.getP(i) - standardCoin.getP(i)); //오차범위 초기화
		cout << i << "번 P " << moe<< ", " << endl;
		if (moe > standardCoin.getMrgErP(i) ) { //오차범위가 지정된 오차범위 값을 넘으면 false를 반환
			return false;
		}
	}
	return true;
}

int main() { //메인함수
	Coin10 coin10;
	Coin50 coin50;
	Coin100 coin100;
	Coin500 coin500;
	
	int cnt10 = 0, cnt50 = 0, cnt100 = 0, cnt500 = 0, mNum = 0, price=0, total=0, targetAmount;
	
	Ticket *slcTicket = nullptr;

	cout << "메뉴를 선택 해주세요" << "\n1.일회용 승차권 2.우대용 3.교통카드 충전" << "\n-----------------------------------------" << endl;
	cin >> mNum;
	if (mNum == 1)
	{
		OTicket oTicket;
		slcTicket = &oTicket;
	}
	else if (mNum == 2)
	{
		PreTicket preTicket;
		slcTicket = &preTicket;
	}
	else if (mNum == 3)
	{
		ChargeTicket chargeTicket;
		slcTicket = &chargeTicket;
	}
	targetAmount = slcTicket->getTargetAmount();
	cout << "총 금액 : " << targetAmount << "원\n" << endl;
	while (true) // 주화 판별 함수를 호출하여 유효한 동전으로 판별되었을 경우, (추후 목표값 달성시까지) 동전 반환 및 프로그램 종료
	{
		cout << "동전을 투입해주세요\n" << endl;
		InsCns insCns;

		if (compareCoins(insCns, coin10)) {
			cnt10++;
			total += 10;
			cout << "10원, count " << cnt10 << "개" << endl;
		}
		else if (compareCoins(insCns, coin50)) {
			cnt50++;
			total += 50;
			cout << "50원, count " << cnt50 << "개" << endl;
		}
		else if (compareCoins(insCns, coin100)) {
			cnt100++;
			total += 100;
			cout << "100원, count " << cnt100 << "개" << endl;
		}
		else if (compareCoins(insCns, coin500)) {
			cnt500++;
			total += 500;
			cout << "500원, count " << cnt500 << "개" << endl;
		}
		else {
			cout << "동전이 반환되었습니다." << endl;
		}

		cout << "투입하신 금액 : " << total << "원\n" << "투입하실 금액 : " << targetAmount - total << "원\n\n" << endl;
		if (targetAmount-total == 0)
		{
			cout << "발권이 완료되었습니다.";
			break;
		}
	}
	return 0;
}

