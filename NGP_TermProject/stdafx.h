// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <queue>

// 전 파일에서 긁어 온거 ==
#include <atlimage.h>
#include <time.h>
#include <random>
#include <list>

#include "../Server/Common.h"


#define WINWIDTH 1600		//윈도우 가로
#define WINHEIGHT 900		//윈도우 세로

#define CARDWIDTH 307		//카드 원본 크기
#define CARDHEIGHT 492		//카드 원본 크기
#define CARDMINIWIDTH 187	//카드 작은 크기
#define CARDMINIHEIGHT 300	//카드 작은 크기
#define CARDVARIABLE 10		//카드 종류

#define MAXHANDCARD 7		//손에 들 수 있는 카드 수		
#define CARDDRAWTERM 300	//60에 1초
#define CARDSPAWNRAND 25	//상점에 트포강화 카드가 안나올 확률 x%
#define MANAREGENERATION 30	//마나 재생

#define MAXWOLF 25
#define MAXBAT 10

#define ULTIMATESKILL 200

#define GROUNDYPOINT 634
#define CASTLEXPOINT 235

#define IDC_BUTTON_BUY1 10001
#define IDC_BUTTON_BUY1 10001
#define IDC_BUTTON_BUY2 10002
#define IDC_BUTTON_BUY3 10003
#define IDC_BUTTON_BUY4 10004

// 1 / 60
#define MAX_FRAMERATE 0.016

enum class CardName : int8_t { N_rhlddufvk, N_sktjsckd, N_dbtjdrkdcjs, N_wjrfydvh, N_aodfyddufvk, N_qksdnjftja, N_dusghkstja, N_cjdfydwls, N_cjdfydcnftn, N_ghltjsckd, N_dmsgkdbtjdxks };
enum class CardRect : int8_t { R_main, R_tier1, R_tier2, R_tier3 };
enum class TriIndex : int8_t { I_Tier1, I_Tier2, I_Tier3, I_selected };


