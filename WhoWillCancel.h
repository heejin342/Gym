#pragma once

class cancel {
public:
	//cancel index
	int index;

	//회원번호(고유 id)
	int cNum;

	//회원이름
	char cName[10];

	//운동 달성 지수 첫-현/첫-목
	double achieve;

	//운동경과 (가장최근운동일-최초등록일)
	int ingDay;

	//운동간격 운동경과/누적운동 : 낮을 수록 자주옴
	double realDay;

	//잔여일 (상품권*1/2 > (상품권 말소시기-오늘날짜) ) > 0 : 거의 끝나감
	int resDay;

};

class find {
public:
	int originIndex;
	int sum;
};

// 1. 잔여일 일정 이하인 사람 대상으로 cancel 리스트에 넣음
// 2. 운동경과/누적운동 작을수록 출석율 좋음 => 누적 운동 0인경우 운동경과
// 3. 출석율 좋은 사람 중 운동 달성 지수 낮은사람
//// 4. 같다면 PT여부 or 오래된 회원인지 체크