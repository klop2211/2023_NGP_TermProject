#include "stdafx.h"
#include "OtherCard.h"
//====================================집중============================================

Wjrfydvh::Wjrfydvh(int** m_iTripord)
{
	__init__();
	this->m_iTripord = m_iTripord;
}

void Wjrfydvh::setTier1()
{
	switch (m_iTripord[(int)CardName::N_wjrfydvh][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//빠른준비1.jpg"));
		lstrcpy(m_tStr[1], L"빠른 준비\n차징 속도가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//반응속도1.jpg"));
		lstrcpy(m_tStr[1], L"사거리 증가\n공격 사거리가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Wjrfydvh::setTier2() {
	switch (m_iTripord[(int)CardName::N_wjrfydvh][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//마력조절2.jpg"));
		lstrcpy(m_tStr[2], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
		m_bCheep = true;
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//공격잇기.jpg"));
		lstrcpy(m_tStr[2], L"카드 뽑기\n무작위 난무카드를 뽑는다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//부위파괴강화2.jpg"));
		lstrcpy(m_tStr[2], L"부위파괴 강화\n.부위 파괴 수치를 +1만큼 증가 시킨다\n");
		break;
	default:
		break;
	}
}

void Wjrfydvh::setTier3() {
	switch (m_iTripord[(int)CardName::N_wjrfydvh][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//치명적인조준.jpg"));
		lstrcpy(m_tStr[3], L"치명적인 조준\n공중의 적에게도 피해를 입힌다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//약점포착3.jpg"));
		lstrcpy(m_tStr[3], L"약점 포착\n보스급 적에게 주는 피해가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Wjrfydvh::__init__()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}

	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_wjrfydvh][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//적룡포3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_wjrfydvh][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//적룡포2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_wjrfydvh][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//적룡포1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//적룡포.jpg"));

	m_eCardname = (CardName)(int)CardName::N_wjrfydvh;
	m_iMana = 8 - m_bCheep, m_iDamage = 15, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"적룡포");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//적룡포.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"자세를 잡고 집중한 뒤 전방으로 창을 찔러 %d의 피해를 준다.\n부위파괴 : %d\0", m_iDamage, m_iDestruction);
}

Sktjsckd::Sktjsckd(int** m_iTripord)
{
	__init__();
	this->m_iTripord = m_iTripord;
}

void Sktjsckd::setTier1() {
	switch (m_iTripord[(int)CardName::N_sktjsckd][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//난무특화.jpg"));
		lstrcpy(m_tStr[1], L"난무 특화\n일반 적에게 입히는 피해가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
		lstrcpy(m_tStr[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//화력조절1.jpg"));
		lstrcpy(m_tStr[1], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
		break;
	default:
		break;
	}
}

void Sktjsckd::setTier2() {
	switch (m_iTripord[(int)CardName::N_sktjsckd][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//공격잇기.jpg"));
		lstrcpy(m_tStr[2], L"연속 공격\n이 스킬을 1회 더 사용한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
		lstrcpy(m_tStr[2], L"약점 타격\n보스급 적에게 주는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//공격잇기.jpg"));
		lstrcpy(m_tStr[2], L"카드 뽑기\n무작위 난무카드를 뽑는다\n");
		break;
	default:
		break;
	}
}

void Sktjsckd::setTier3() {
	switch (m_iTripord[(int)CardName::N_sktjsckd][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//기술강화.jpg"));
		lstrcpy(m_tStr[3], L"기술 강화\n스킬의 사거리가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//치명적인조준.jpg"));
		lstrcpy(m_tStr[3], L"강화된 창\n데미지가 감소하지만, 맵끝까지 날라가는 창을 던진다.\n");
		break;
	default:
		break;
	}
}

void Sktjsckd::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();
	if (m_iTripord[(int)CardName::N_sktjsckd][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//나선창3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_sktjsckd][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//나선창2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_sktjsckd][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//나선창1.png"));
		setTier1();
	}
	else {
		m_cImg[0].Load(TEXT(".//카드관련//카드//나선창.jpg"));
	}
	m_eCardname = (CardName)(int)CardName::N_sktjsckd;
	m_iMana = 1, m_iDamage = 7, m_iNeutralization = 5, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"나선창");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//나선창.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"창으로 간결하게 찔러 %d의 피해를 준다.\n\0", m_iDamage);
}

Rhlddufvk::Rhlddufvk(int** m_iTripord)
{
	__init__();
	this->m_iTripord = m_iTripord;
}

void Rhlddufvk::setTier1() {
	switch (m_iTripord[(int)CardName::N_rhlddufvk][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//부위파괴강화1.jpg"));
		lstrcpy(m_tStr[1], L"부위파괴 강화\n부위 파괴 수치를 +1만큼 증가 시킨다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//빠른준비1.jpg"));
		lstrcpy(m_tStr[1], L"공격 속도 증가\n공격 속도가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
		lstrcpy(m_tStr[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Rhlddufvk::setTier2() {
	switch (m_iTripord[(int)CardName::N_rhlddufvk][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//화염회전.jpg"));
		lstrcpy(m_tStr[2], L"화염 회전\n적중한 적에게 화상을 부여한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//절대방어.jpg"));
		lstrcpy(m_tStr[2], L"절대 방어\n적중한 적을 창 끝까지 밀쳐낸다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
		lstrcpy(m_tStr[2], L"데미지 증가\n보스급 적에게 주는 피해가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Rhlddufvk::setTier3() {
	switch (m_iTripord[(int)CardName::N_rhlddufvk][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//돌격베기.jpg"));
		lstrcpy(m_tStr[3], L"차지 강화\n차징 스킬로 바뀌고 주는 피해와 사거리가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//마력조절3.jpg"));
		lstrcpy(m_tStr[3], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
		m_bCheep = true;
		break;
	default:
		break;
	}
}

void Rhlddufvk::__init__() {
	for (int i = 0; i < 4; i++)
	{
		//if (m_cImg[i] != nullptr)
		m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_rhlddufvk][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//굉열파3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_rhlddufvk][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//굉열파2.png"));
		setTier1();
		setTier2();
	}
	else if (m_iTripord[(int)CardName::N_rhlddufvk][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//굉열파1.png"));
		setTier1();
	}
	else {
		m_cImg[0].Load(TEXT(".//카드관련//카드//굉열파.jpg"));
	}

	m_eCardname = (CardName)(int)CardName::N_rhlddufvk;
	m_iMana = 3 - m_bCheep, m_iDamage = 10, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"굉열파");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//굉열파.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"창에 기를 모아 가까운 적에게 %d피해를 준다.\n부위파괴 : %d\0", m_iDamage, m_iDestruction);
}


Dbtjdrkdcjs::Dbtjdrkdcjs(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Dbtjdrkdcjs::setTier1() {
	switch (m_iTripord[(int)CardName::N_dbtjdrkdcjs][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//빠른준비1.jpg"));
		lstrcpy(m_tStr[1], L"빠른 공격\n공격 속도가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//난무특화.jpg"));
		lstrcpy(m_tStr[1], L"난무 특화\n일반 적에게 입히는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//약점포착1.jpg"));
		lstrcpy(m_tStr[1], L"약점 포착\n보스급 적에게 주는 피해가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Dbtjdrkdcjs::setTier2() {
	switch (m_iTripord[(int)CardName::N_dbtjdrkdcjs][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//기절효과.jpg"));
		lstrcpy(m_tStr[2], L"기절 공격\n적중한 적을 기절시킨다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//화염회전.jpg"));
		lstrcpy(m_tStr[2], L"화염 지대\n착지 위치에 화상을 부여하는 화염지대를 생성한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//대지파괴.jpg"));
		lstrcpy(m_tStr[2], L"대지 생성\n착지 테두리에 적의 접근을 막는 벽을 생성한다.\n");
		break;
	default:
		break;
	}
}

void Dbtjdrkdcjs::setTier3() {
	switch (m_iTripord[(int)CardName::N_dbtjdrkdcjs][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//강력한마무리.jpg"));
		lstrcpy(m_tStr[3], L"강화 착지\n착지 후 좌우로 창이 떨어진다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//치명적인조준.jpg"));
		lstrcpy(m_tStr[3], L"마술 투창\n점프를 하지 않으며, 창을 하늘에서 떨어지게 한다.\n");
		break;
	default:
		break;
	}
}

void Dbtjdrkdcjs::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_dbtjdrkdcjs][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//유성강천3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_dbtjdrkdcjs][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//유성강천2.png"));
		setTier1();
		setTier2();
	}
	else if (m_iTripord[(int)CardName::N_dbtjdrkdcjs][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//유성강천1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//유성강천.jpg"));

	m_eCardname = (CardName)(int)CardName::N_dbtjdrkdcjs;
	m_iMana = 7, m_iDamage = 12, m_iNeutralization = 5, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"유성강천");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//유성강천.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"위로 점프하여 내리 꽂아 충격파를 일으켜 %d의 피해를 준다.\n\0", m_iDamage);
}

//==========================난무======================================

Aodfyddufvk::Aodfyddufvk(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Aodfyddufvk::setTier1() {
	switch (m_iTripord[(int)CardName::N_aodfyddufvk][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//넓은공격.jpg"));
		lstrcpy(m_tStr[1], L"넓은 공격\n공격 범위가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//뇌진탕.jpg"));
		lstrcpy(m_tStr[1], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Aodfyddufvk::setTier2() {
	switch (m_iTripord[(int)CardName::N_aodfyddufvk][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//빠른준비2.jpg"));
		lstrcpy(m_tStr[2], L"공격 속도 증가\n공격 속도가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//냉기회전.jpg"));
		lstrcpy(m_tStr[2], L"수속성 부여\n적중한 적에게 빙결을 부여한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//화염회전.jpg"));
		lstrcpy(m_tStr[2], L"화속성 부여\n적중한 적에게 화상을 부여한다.\n");
		break;
	default:
		break;
	}
}

void Aodfyddufvk::setTier3() {
	switch (m_iTripord[(int)CardName::N_aodfyddufvk][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//공격잇기3.jpg"));
		lstrcpy(m_tStr[3], L"연속 공격\n이 스킬을 1회 더 사용한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//마력조절3.jpg"));
		lstrcpy(m_tStr[3], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
		m_bCheep = true;
		break;
	default:
		break;
	}
}

void Aodfyddufvk::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_aodfyddufvk][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//맹룡열파3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_aodfyddufvk][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//맹룡열파2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_aodfyddufvk][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//맹룡열파1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//맹룡열파.jpg"));

	m_eCardname = (CardName)(int)CardName::N_aodfyddufvk;
	m_iMana = 6 - m_bCheep, m_iDamage = 10, m_iNeutralization = 15, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"맹룡열파");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//맹룡열파.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"더욱 큰 창으로 바뀌고 크게 휘둘러 %d의 피해를 준다.\n무력화 : 중\0", m_iDamage);
}

Qksdnjftja::Qksdnjftja(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Qksdnjftja::setTier1() {
	switch (m_iTripord[(int)CardName::N_qksdnjftja][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//부위파괴강화1.jpg"));
		lstrcpy(m_tStr[1], L"부위파괴 강화\n부위 파괴 수치를 +1만큼 증가 시킨다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
		lstrcpy(m_tStr[1], L"탁월한 기동성\n스킬의 전진 거리가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Qksdnjftja::setTier2() {
	switch (m_iTripord[(int)CardName::N_qksdnjftja][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//뇌진탕2.jpg"));
		lstrcpy(m_tStr[2], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
		lstrcpy(m_tStr[2], L"약점 타격\n보스급 적에게 주는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//마력조절2.jpg"));
		lstrcpy(m_tStr[2], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
		m_bCheep = true;
		break;
	default:
		break;
	}
}

void Qksdnjftja::setTier3() {
	switch (m_iTripord[(int)CardName::N_qksdnjftja][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//강력한마무리.jpg"));
		lstrcpy(m_tStr[3], L"밀고 나가기\n보는 방향으로 돌진하며 일반몹을 끌고간다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//날이선일격.jpg"));
		lstrcpy(m_tStr[3], L"회오리 생성\n마무리 공격이 회오리를 생성한다.\n");
		break;
	default:
		break;
	}
}
void Qksdnjftja::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_qksdnjftja][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//반월섬3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_qksdnjftja][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//반월섬2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_qksdnjftja][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//반월섬1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//반월섬.jpg"));

	m_eCardname = (CardName)(int)CardName::N_qksdnjftja;
	m_iMana = 7 - m_bCheep, m_iDamage = 12, m_iNeutralization = 20; m_iDestruction = 2;

	lstrcpy(m_tNameStr, L"반월섬");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//반월섬.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"전방으로 긴창을 바닥에 끌면서 이동하여 %d의 피해를 준다.\n무력화 : 중상\0", m_iDamage);
}

Dusghkstja::Dusghkstja(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Dusghkstja::setTier1() {
	switch (m_iTripord[(int)CardName::N_dusghkstja][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n전진하지 않으며, 적에게 주는 피해가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
		lstrcpy(m_tStr[1], L"탁월한 기동성\n스킬의 전진 거리가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//화력조절1.jpg"));
		lstrcpy(m_tStr[1], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
		break;
	default:
		break;
	}
}

void Dusghkstja::setTier2() {
	switch (m_iTripord[(int)CardName::N_dusghkstja][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//빠른준비2.jpg"));
		lstrcpy(m_tStr[2], L"공격 속도 증가\n공격 속도가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//뇌진탕.jpg"));
		lstrcpy(m_tStr[2], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//파괴하는창.jpg"));
		lstrcpy(m_tStr[2], L"파괴하는 창\n적에게 주는 피해가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Dusghkstja::setTier3() {
	switch (m_iTripord[(int)CardName::N_dusghkstja][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//강력한마무리.jpg"));
		lstrcpy(m_tStr[3], L"카드 뽑기\n카드를 한 장 뽑지만, 소모되는 마나를 증가시킨다.\n");
		m_bCheep = true;
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//광휘의창.jpg"));
		lstrcpy(m_tStr[3], L"검기 생성\n공격이 검기를 생성하지만, 소모되는 마나를 증가시킨다.\n");
		m_bCheep = true;
		break;
	default:
		break;
	}
}

void Dusghkstja::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_dusghkstja][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//연환섬3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_dusghkstja][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//연환섬2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_dusghkstja][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//연환섬1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//연환섬.jpg"));

	m_eCardname = (CardName)(int)CardName::N_dusghkstja;
	m_iMana = 2 + m_bCheep, m_iDamage = 6, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"연환섬");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//연환섬.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"창을 위로 올려친 후 앞으로 전진하여 베기공격을하여 %d의 피해를 준다.\n부위파괴 : %d\0", m_iDamage, m_iDestruction);
}

Cjdfydwls::Cjdfydwls(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Cjdfydwls::setTier1() {
	switch (m_iTripord[(int)CardName::N_cjdfydwls][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//뇌진탕.jpg"));
		lstrcpy(m_tStr[1], L"뇌진탕\n적에게 주는 무력화가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//넓은공격.jpg"));
		lstrcpy(m_tStr[1], L"넓은 공격\n공격 범위가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Cjdfydwls::setTier2() {
	switch (m_iTripord[(int)CardName::N_cjdfydwls][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//내려치는창.jpg"));
		lstrcpy(m_tStr[2], L"창 소환\n창을 찍지 않는 대신 창을 소환하여 떨군다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//집중공략.jpg"));
		lstrcpy(m_tStr[2], L"집중 공격\n공격 범위가 감소하지만, 데미지가 크게 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//대지파괴.jpg"));
		lstrcpy(m_tStr[2], L"토속성 부여\n적의 접근을 막는 벽을 생성한다.\n");
		break;
	default:
		break;
	}
}

void Cjdfydwls::setTier3() {
	switch (m_iTripord[(int)CardName::N_cjdfydwls][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//공격잇기3.jpg"));
		lstrcpy(m_tStr[3], L"카드 뽑기\n카드를 한 장 뽑는다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//마력조절3.jpg"));
		lstrcpy(m_tStr[3], L"마력 조절\n소모되는 마나를 감소시킨다.\n");
		m_bCheep = true;
		break;
	default:
		break;
	}
}

void Cjdfydwls::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_cjdfydwls][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡진3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydwls][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡진2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydwls][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡진1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡진.jpg"));

	m_eCardname = (CardName)(int)CardName::N_cjdfydwls;
	m_iMana = 1 - m_bCheep, m_iDamage = 5, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"청룡진");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//청룡진.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"제자리에서 창을 강하게 내려찍어 충격파가 퍼져 %d의 피해를 준다.\n부위파괴 : %d\0", m_iDamage, m_iDestruction);
}

Cjdfydcnftn::Cjdfydcnftn(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Cjdfydcnftn::setTier1() {
	switch (m_iTripord[(int)CardName::N_cjdfydcnftn][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//치명적인공격.jpg"));
		lstrcpy(m_tStr[1], L"공격 강화\n돌진을 하지 않지만, 데미지가 크게 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
		lstrcpy(m_tStr[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Cjdfydcnftn::setTier2() {
	switch (m_iTripord[(int)CardName::N_cjdfydcnftn][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//나선찌르기.jpg"));
		lstrcpy(m_tStr[2], L"풍속성 부여\n위 아래 적을 끌어당긴다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//화력조절2.jpg"));
		lstrcpy(m_tStr[2], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//넓은타격.jpg"));
		lstrcpy(m_tStr[2], L"넓은 공격\n공격 범위가 증가한다.\n");
		break;
	default:
		break;
	}
}

void Cjdfydcnftn::setTier3() {
	switch (m_iTripord[(int)CardName::N_cjdfydcnftn][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//돌격베기.jpg"));
		lstrcpy(m_tStr[3], L"창 설치\n회전하는 창을 설치한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//날이선일격.jpg"));
		lstrcpy(m_tStr[3], L"위성\n공격 후 주인공 주위를 도는 작은 창을 생성한다.\n");
		break;
	default:
		break;
	}
}

void Cjdfydcnftn::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_cjdfydcnftn][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡출수3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydcnftn][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡출수2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydcnftn][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡출수1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//청룡출수.jpg"));

	m_eCardname = (CardName)(int)CardName::N_cjdfydcnftn;
	m_iMana = 3, m_iDamage = 5, m_iNeutralization = 15, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"청룡출수");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//청룡출수.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"전방으로 전진한 후 창을 빠르게 휘둘러 %d의 피해를 준다.\n무력화 : 중\0", m_iDamage);
}

Ghltjsckd::Ghltjsckd(int** m_iTripord, bool BOnce) {
	once = BOnce;
	__init__();
	this->m_iTripord = m_iTripord;
}

//Ghltjsckd(bool a) : Card() {
//	once = true;
//	__init__();
//}

void Ghltjsckd::setTier1() {
	switch (m_iTripord[(int)CardName::N_ghltjsckd][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//탁월한기동성.jpg"));
		lstrcpy(m_tStr[1], L"탁월한 기동성\n사용 후 이동속도가 증가한다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//급소타격.jpg"));
		lstrcpy(m_tStr[1], L"급소 타격\n적에게 주는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//카드관련//트포//회전올려치기.jpg"));
		lstrcpy(m_tStr[1], L"빠른 마무리\n1회만 회전한다.\n");
		break;
	default:
		break;
	}
}

void Ghltjsckd::setTier2() {
	switch (m_iTripord[(int)CardName::N_ghltjsckd][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//정신파괴.jpg"));
		lstrcpy(m_tStr[2], L"강한 바람\n마지막 공격이 적을 눕힌다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//약점타격.jpg"));
		lstrcpy(m_tStr[2], L"약점 타격\n보스급 적에게 주는 피해가 증가한다.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//카드관련//트포//화력조절2.jpg"));
		lstrcpy(m_tStr[2], L"게이지 수급\n각성기 게이지를 추가 수급한다.\n");
		break;
	default:
		break;
	}
}

void Ghltjsckd::setTier3() {
	switch (m_iTripord[(int)CardName::N_ghltjsckd][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//연속회전.jpg"));
		lstrcpy(m_tStr[3], L"연속 공격\n이 카드를 1회 가져온다.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//카드관련//트포//공격잇기3.jpg"));
		lstrcpy(m_tStr[3], L"카드 뽑기\n덱에서 무작위 집중 카드를 1장 뽑는다.\n");
		break;
	default:
		break;
	}
}

void Ghltjsckd::__init__() {
	for (int i = 0; i < 4; i++)
	{
		if (m_cImg[i] != nullptr)
			m_cImg[i].Destroy();
	}
	if (m_cSkill != nullptr)
		m_cSkill.Destroy();
	if (m_cEffect != nullptr)
		m_cEffect.Destroy();

	if (m_iTripord[(int)CardName::N_ghltjsckd][2] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//회선창3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_ghltjsckd][1] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//회선창2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_ghltjsckd][0] != 0) {
		m_cImg[0].Load(TEXT(".//카드관련//카드//회선창1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//카드관련//카드//회선창.jpg"));

	m_eCardname = (CardName)(int)CardName::N_ghltjsckd;
	m_iMana = 5, m_iDamage = 9, m_iNeutralization = 10, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"회선창");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//회선창.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"전방으로 회전하여 %d의 피해를 준다.\n무력화 : 하\0", m_iDamage);
}

Dmsgkdbtjdxks::Dmsgkdbtjdxks() {
	//if (m_iTripord[N_dmsgkdbtjdxks][2] != 0)
	//	m_cImg[0].Load(TEXT(".//카드관련//카드//은하유성탄3.png"));
	//else if (m_iTripord[N_dmsgkdbtjdxks][1] != 0)
	//	m_cImg[0].Load(TEXT(".//카드관련//카드//은하유성탄2.png"));
	//else if (m_iTripord[N_dmsgkdbtjdxks][0] != 0)
	//	m_cImg[0].Load(TEXT(".//카드관련//카드//은하유성탄1.png"));
	//else
	m_cImg[0].Load(TEXT(".//카드관련//카드//은하유성탄.jpg"));

	m_eCardname = (CardName)(int)CardName::N_dmsgkdbtjdxks;
	m_iMana = 10, m_iDamage = 20, m_iNeutralization = 40, m_iDestruction = 2;

	lstrcpy(m_tNameStr, L"은하유성탄");
	m_cSkill.Load(TEXT(".//카드관련//스킬초상화//은하유성탄.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"위로 점프한 후 창을 던진다. 창이 땅에 떨어지면 %d의 피해를 주고 서서히 폭발한다.\n부위파괴 : %d, 무력화 : 최상\0", m_iDamage, m_iDestruction);
}