#include "stdafx.h"
#include "OtherCard.h"
//====================================����============================================

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
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����غ�1.jpg"));
		lstrcpy(m_tStr[1], L"���� �غ�\n��¡ �ӵ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����ӵ�1.jpg"));
		lstrcpy(m_tStr[1], L"��Ÿ� ����\n���� ��Ÿ��� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Wjrfydvh::setTier2() {
	switch (m_iTripord[(int)CardName::N_wjrfydvh][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//��������2.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
		m_bCheep = true;
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ձ�.jpg"));
		lstrcpy(m_tStr[2], L"ī�� �̱�\n������ ����ī�带 �̴´�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı���ȭ2.jpg"));
		lstrcpy(m_tStr[2], L"�����ı� ��ȭ\n.���� �ı� ��ġ�� +1��ŭ ���� ��Ų��\n");
		break;
	default:
		break;
	}
}

void Wjrfydvh::setTier3() {
	switch (m_iTripord[(int)CardName::N_wjrfydvh][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//ġ����������.jpg"));
		lstrcpy(m_tStr[3], L"ġ������ ����\n������ �����Ե� ���ظ� ������.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
		lstrcpy(m_tStr[3], L"���� ����\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_wjrfydvh][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_wjrfydvh][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������.jpg"));

	m_eCardname = (CardName)(int)CardName::N_wjrfydvh;
	m_iMana = 8 - m_bCheep, m_iDamage = 15, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"������");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"�ڼ��� ��� ������ �� �������� â�� �� %d�� ���ظ� �ش�.\n�����ı� : %d\0", m_iDamage, m_iDestruction);
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
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//����Ưȭ.jpg"));
		lstrcpy(m_tStr[1], L"���� Ưȭ\n�Ϲ� ������ ������ ���ذ� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
		lstrcpy(m_tStr[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//ȭ������1.jpg"));
		lstrcpy(m_tStr[1], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Sktjsckd::setTier2() {
	switch (m_iTripord[(int)CardName::N_sktjsckd][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ձ�.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n�� ��ų�� 1ȸ �� ����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
		lstrcpy(m_tStr[2], L"���� Ÿ��\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ձ�.jpg"));
		lstrcpy(m_tStr[2], L"ī�� �̱�\n������ ����ī�带 �̴´�\n");
		break;
	default:
		break;
	}
}

void Sktjsckd::setTier3() {
	switch (m_iTripord[(int)CardName::N_sktjsckd][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ȭ.jpg"));
		lstrcpy(m_tStr[3], L"��� ��ȭ\n��ų�� ��Ÿ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//ġ����������.jpg"));
		lstrcpy(m_tStr[3], L"��ȭ�� â\n�������� ����������, �ʳ����� ���󰡴� â�� ������.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//����â3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_sktjsckd][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//����â2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_sktjsckd][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//����â1.png"));
		setTier1();
	}
	else {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//����â.jpg"));
	}
	m_eCardname = (CardName)(int)CardName::N_sktjsckd;
	m_iMana = 1, m_iDamage = 7, m_iNeutralization = 5, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"����â");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//����â.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"â���� �����ϰ� �� %d�� ���ظ� �ش�.\n\0", m_iDamage);
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
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����ı���ȭ1.jpg"));
		lstrcpy(m_tStr[1], L"�����ı� ��ȭ\n���� �ı� ��ġ�� +1��ŭ ���� ��Ų��.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����غ�1.jpg"));
		lstrcpy(m_tStr[1], L"���� �ӵ� ����\n���� �ӵ��� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
		lstrcpy(m_tStr[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Rhlddufvk::setTier2() {
	switch (m_iTripord[(int)CardName::N_rhlddufvk][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ��ȸ��.jpg"));
		lstrcpy(m_tStr[2], L"ȭ�� ȸ��\n������ ������ ȭ���� �ο��Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
		lstrcpy(m_tStr[2], L"���� ���\n������ ���� â ������ ���ĳ���.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
		lstrcpy(m_tStr[2], L"������ ����\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Rhlddufvk::setTier3() {
	switch (m_iTripord[(int)CardName::N_rhlddufvk][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//���ݺ���.jpg"));
		lstrcpy(m_tStr[3], L"���� ��ȭ\n��¡ ��ų�� �ٲ�� �ִ� ���ؿ� ��Ÿ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
		lstrcpy(m_tStr[3], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_rhlddufvk][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������2.png"));
		setTier1();
		setTier2();
	}
	else if (m_iTripord[(int)CardName::N_rhlddufvk][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������1.png"));
		setTier1();
	}
	else {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������.jpg"));
	}

	m_eCardname = (CardName)(int)CardName::N_rhlddufvk;
	m_iMana = 3 - m_bCheep, m_iDamage = 10, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"������");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"â�� �⸦ ��� ����� ������ %d���ظ� �ش�.\n�����ı� : %d\0", m_iDamage, m_iDestruction);
}


Dbtjdrkdcjs::Dbtjdrkdcjs(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Dbtjdrkdcjs::setTier1() {
	switch (m_iTripord[(int)CardName::N_dbtjdrkdcjs][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����غ�1.jpg"));
		lstrcpy(m_tStr[1], L"���� ����\n���� �ӵ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//����Ưȭ.jpg"));
		lstrcpy(m_tStr[1], L"���� Ưȭ\n�Ϲ� ������ ������ ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//��������1.jpg"));
		lstrcpy(m_tStr[1], L"���� ����\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Dbtjdrkdcjs::setTier2() {
	switch (m_iTripord[(int)CardName::N_dbtjdrkdcjs][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����ȿ��.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n������ ���� ������Ų��.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ��ȸ��.jpg"));
		lstrcpy(m_tStr[2], L"ȭ�� ����\n���� ��ġ�� ȭ���� �ο��ϴ� ȭ�����븦 �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı�.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n���� �׵θ��� ���� ������ ���� ���� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Dbtjdrkdcjs::setTier3() {
	switch (m_iTripord[(int)CardName::N_dbtjdrkdcjs][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����Ѹ�����.jpg"));
		lstrcpy(m_tStr[3], L"��ȭ ����\n���� �� �¿�� â�� ��������.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//ġ����������.jpg"));
		lstrcpy(m_tStr[3], L"���� ��â\n������ ���� ������, â�� �ϴÿ��� �������� �Ѵ�.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������õ3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_dbtjdrkdcjs][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������õ2.png"));
		setTier1();
		setTier2();
	}
	else if (m_iTripord[(int)CardName::N_dbtjdrkdcjs][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������õ1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//������õ.jpg"));

	m_eCardname = (CardName)(int)CardName::N_dbtjdrkdcjs;
	m_iMana = 7, m_iDamage = 12, m_iNeutralization = 5, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"������õ");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//������õ.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"���� �����Ͽ� ���� �Ⱦ� ����ĸ� ������ %d�� ���ظ� �ش�.\n\0", m_iDamage);
}

//==========================����======================================

Aodfyddufvk::Aodfyddufvk(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Aodfyddufvk::setTier1() {
	switch (m_iTripord[(int)CardName::N_aodfyddufvk][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//��������.jpg"));
		lstrcpy(m_tStr[1], L"���� ����\n���� ������ �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
		lstrcpy(m_tStr[1], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Aodfyddufvk::setTier2() {
	switch (m_iTripord[(int)CardName::N_aodfyddufvk][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����غ�2.jpg"));
		lstrcpy(m_tStr[2], L"���� �ӵ� ����\n���� �ӵ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�ñ�ȸ��.jpg"));
		lstrcpy(m_tStr[2], L"���Ӽ� �ο�\n������ ������ ������ �ο��Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ��ȸ��.jpg"));
		lstrcpy(m_tStr[2], L"ȭ�Ӽ� �ο�\n������ ������ ȭ���� �ο��Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Aodfyddufvk::setTier3() {
	switch (m_iTripord[(int)CardName::N_aodfyddufvk][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ձ�3.jpg"));
		lstrcpy(m_tStr[3], L"���� ����\n�� ��ų�� 1ȸ �� ����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
		lstrcpy(m_tStr[3], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_aodfyddufvk][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_aodfyddufvk][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ͷ濭��.jpg"));

	m_eCardname = (CardName)(int)CardName::N_aodfyddufvk;
	m_iMana = 6 - m_bCheep, m_iDamage = 10, m_iNeutralization = 15, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"�ͷ濭��");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ͷ濭��.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"���� ū â���� �ٲ�� ũ�� �ֵѷ� %d�� ���ظ� �ش�.\n����ȭ : ��\0", m_iDamage);
}

Qksdnjftja::Qksdnjftja(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Qksdnjftja::setTier1() {
	switch (m_iTripord[(int)CardName::N_qksdnjftja][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�����ı���ȭ1.jpg"));
		lstrcpy(m_tStr[1], L"�����ı� ��ȭ\n���� �ı� ��ġ�� +1��ŭ ���� ��Ų��.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
		lstrcpy(m_tStr[1], L"Ź���� �⵿��\n��ų�� ���� �Ÿ��� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Qksdnjftja::setTier2() {
	switch (m_iTripord[(int)CardName::N_qksdnjftja][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//������2.jpg"));
		lstrcpy(m_tStr[2], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
		lstrcpy(m_tStr[2], L"���� Ÿ��\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//��������2.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
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
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����Ѹ�����.jpg"));
		lstrcpy(m_tStr[3], L"�а� ������\n���� �������� �����ϸ� �Ϲݸ��� ������.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//���̼��ϰ�.jpg"));
		lstrcpy(m_tStr[3], L"ȸ���� ����\n������ ������ ȸ������ �����Ѵ�.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ݿ���3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_qksdnjftja][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ݿ���2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_qksdnjftja][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ݿ���1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//�ݿ���.jpg"));

	m_eCardname = (CardName)(int)CardName::N_qksdnjftja;
	m_iMana = 7 - m_bCheep, m_iDamage = 12, m_iNeutralization = 20; m_iDestruction = 2;

	lstrcpy(m_tNameStr, L"�ݿ���");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//�ݿ���.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"�������� ��â�� �ٴڿ� ���鼭 �̵��Ͽ� %d�� ���ظ� �ش�.\n����ȭ : �߻�\0", m_iDamage);
}

Dusghkstja::Dusghkstja(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Dusghkstja::setTier1() {
	switch (m_iTripord[(int)CardName::N_dusghkstja][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n�������� ������, ������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
		lstrcpy(m_tStr[1], L"Ź���� �⵿��\n��ų�� ���� �Ÿ��� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//ȭ������1.jpg"));
		lstrcpy(m_tStr[1], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Dusghkstja::setTier2() {
	switch (m_iTripord[(int)CardName::N_dusghkstja][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����غ�2.jpg"));
		lstrcpy(m_tStr[2], L"���� �ӵ� ����\n���� �ӵ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
		lstrcpy(m_tStr[2], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�ı��ϴ�â.jpg"));
		lstrcpy(m_tStr[2], L"�ı��ϴ� â\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Dusghkstja::setTier3() {
	switch (m_iTripord[(int)CardName::N_dusghkstja][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����Ѹ�����.jpg"));
		lstrcpy(m_tStr[3], L"ī�� �̱�\nī�带 �� �� ������, �Ҹ�Ǵ� ������ ������Ų��.\n");
		m_bCheep = true;
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//������â.jpg"));
		lstrcpy(m_tStr[3], L"�˱� ����\n������ �˱⸦ ����������, �Ҹ�Ǵ� ������ ������Ų��.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//��ȯ��3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_dusghkstja][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//��ȯ��2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_dusghkstja][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//��ȯ��1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//��ȯ��.jpg"));

	m_eCardname = (CardName)(int)CardName::N_dusghkstja;
	m_iMana = 2 + m_bCheep, m_iDamage = 6, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"��ȯ��");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��ȯ��.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"â�� ���� �÷�ģ �� ������ �����Ͽ� ����������Ͽ� %d�� ���ظ� �ش�.\n�����ı� : %d\0", m_iDamage, m_iDestruction);
}

Cjdfydwls::Cjdfydwls(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Cjdfydwls::setTier1() {
	switch (m_iTripord[(int)CardName::N_cjdfydwls][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//������.jpg"));
		lstrcpy(m_tStr[1], L"������\n������ �ִ� ����ȭ�� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//��������.jpg"));
		lstrcpy(m_tStr[1], L"���� ����\n���� ������ �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Cjdfydwls::setTier2() {
	switch (m_iTripord[(int)CardName::N_cjdfydwls][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����ġ��â.jpg"));
		lstrcpy(m_tStr[2], L"â ��ȯ\nâ�� ���� �ʴ� ��� â�� ��ȯ�Ͽ� ������.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//���߰���.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n���� ������ ����������, �������� ũ�� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı�.jpg"));
		lstrcpy(m_tStr[2], L"��Ӽ� �ο�\n���� ������ ���� ���� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Cjdfydwls::setTier3() {
	switch (m_iTripord[(int)CardName::N_cjdfydwls][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ձ�3.jpg"));
		lstrcpy(m_tStr[3], L"ī�� �̱�\nī�带 �� �� �̴´�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//��������3.jpg"));
		lstrcpy(m_tStr[3], L"���� ����\n�Ҹ�Ǵ� ������ ���ҽ�Ų��.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û����3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydwls][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û����2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydwls][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û����1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û����.jpg"));

	m_eCardname = (CardName)(int)CardName::N_cjdfydwls;
	m_iMana = 1 - m_bCheep, m_iDamage = 5, m_iNeutralization = 5, m_iDestruction = 1;

	lstrcpy(m_tNameStr, L"û����");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û����.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"���ڸ����� â�� ���ϰ� ������� ����İ� ���� %d�� ���ظ� �ش�.\n�����ı� : %d\0", m_iDamage, m_iDestruction);
}

Cjdfydcnftn::Cjdfydcnftn(int** m_iTripord) {
	__init__();
	this->m_iTripord = m_iTripord;
}

void Cjdfydcnftn::setTier1() {
	switch (m_iTripord[(int)CardName::N_cjdfydcnftn][0])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//ġ�����ΰ���.jpg"));
		lstrcpy(m_tStr[1], L"���� ��ȭ\n������ ���� ������, �������� ũ�� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
		lstrcpy(m_tStr[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Cjdfydcnftn::setTier2() {
	switch (m_iTripord[(int)CardName::N_cjdfydcnftn][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�������.jpg"));
		lstrcpy(m_tStr[2], L"ǳ�Ӽ� �ο�\n�� �Ʒ� ���� �������.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ������2.jpg"));
		lstrcpy(m_tStr[2], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
		lstrcpy(m_tStr[2], L"���� ����\n���� ������ �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Cjdfydcnftn::setTier3() {
	switch (m_iTripord[(int)CardName::N_cjdfydcnftn][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//���ݺ���.jpg"));
		lstrcpy(m_tStr[3], L"â ��ġ\nȸ���ϴ� â�� ��ġ�Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//���̼��ϰ�.jpg"));
		lstrcpy(m_tStr[3], L"����\n���� �� ���ΰ� ������ ���� ���� â�� �����Ѵ�.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û�����3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydcnftn][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û�����2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_cjdfydcnftn][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û�����1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//û�����.jpg"));

	m_eCardname = (CardName)(int)CardName::N_cjdfydcnftn;
	m_iMana = 3, m_iDamage = 5, m_iNeutralization = 15, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"û�����");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//û�����.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"�������� ������ �� â�� ������ �ֵѷ� %d�� ���ظ� �ش�.\n����ȭ : ��\0", m_iDamage);
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
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//Ź���ѱ⵿��.jpg"));
		lstrcpy(m_tStr[1], L"Ź���� �⵿��\n��� �� �̵��ӵ��� �����Ѵ�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//�޼�Ÿ��.jpg"));
		lstrcpy(m_tStr[1], L"�޼� Ÿ��\n������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier1].Load(TEXT(".//ī�����//Ʈ��//ȸ���÷�ġ��.jpg"));
		lstrcpy(m_tStr[1], L"���� ������\n1ȸ�� ȸ���Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Ghltjsckd::setTier2() {
	switch (m_iTripord[(int)CardName::N_ghltjsckd][1])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//�����ı�.jpg"));
		lstrcpy(m_tStr[2], L"���� �ٶ�\n������ ������ ���� ������.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//����Ÿ��.jpg"));
		lstrcpy(m_tStr[2], L"���� Ÿ��\n������ ������ �ִ� ���ذ� �����Ѵ�.\n");
		break;
	case 3:
		m_cImg[(int)CardRect::R_tier2].Load(TEXT(".//ī�����//Ʈ��//ȭ������2.jpg"));
		lstrcpy(m_tStr[2], L"������ ����\n������ �������� �߰� �����Ѵ�.\n");
		break;
	default:
		break;
	}
}

void Ghltjsckd::setTier3() {
	switch (m_iTripord[(int)CardName::N_ghltjsckd][2])
	{
	case 1:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//����ȸ��.jpg"));
		lstrcpy(m_tStr[3], L"���� ����\n�� ī�带 1ȸ �����´�.\n");
		break;
	case 2:
		m_cImg[(int)CardRect::R_tier3].Load(TEXT(".//ī�����//Ʈ��//�����ձ�3.jpg"));
		lstrcpy(m_tStr[3], L"ī�� �̱�\n������ ������ ���� ī�带 1�� �̴´�.\n");
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
		m_cImg[0].Load(TEXT(".//ī�����//ī��//ȸ��â3.png"));
		setTier3();
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_ghltjsckd][1] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//ȸ��â2.png"));
		setTier2();
		setTier1();
	}
	else if (m_iTripord[(int)CardName::N_ghltjsckd][0] != 0) {
		m_cImg[0].Load(TEXT(".//ī�����//ī��//ȸ��â1.png"));
		setTier1();
	}
	else
		m_cImg[0].Load(TEXT(".//ī�����//ī��//ȸ��â.jpg"));

	m_eCardname = (CardName)(int)CardName::N_ghltjsckd;
	m_iMana = 5, m_iDamage = 9, m_iNeutralization = 10, m_iDestruction = 0;

	lstrcpy(m_tNameStr, L"ȸ��â");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//ȸ��â.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"�������� ȸ���Ͽ� %d�� ���ظ� �ش�.\n����ȭ : ��\0", m_iDamage);
}

Dmsgkdbtjdxks::Dmsgkdbtjdxks() {
	//if (m_iTripord[N_dmsgkdbtjdxks][2] != 0)
	//	m_cImg[0].Load(TEXT(".//ī�����//ī��//��������ź3.png"));
	//else if (m_iTripord[N_dmsgkdbtjdxks][1] != 0)
	//	m_cImg[0].Load(TEXT(".//ī�����//ī��//��������ź2.png"));
	//else if (m_iTripord[N_dmsgkdbtjdxks][0] != 0)
	//	m_cImg[0].Load(TEXT(".//ī�����//ī��//��������ź1.png"));
	//else
	m_cImg[0].Load(TEXT(".//ī�����//ī��//��������ź.jpg"));

	m_eCardname = (CardName)(int)CardName::N_dmsgkdbtjdxks;
	m_iMana = 10, m_iDamage = 20, m_iNeutralization = 40, m_iDestruction = 2;

	lstrcpy(m_tNameStr, L"��������ź");
	m_cSkill.Load(TEXT(".//ī�����//��ų�ʻ�ȭ//��������ź.png"));
	swprintf_s(m_tStr[(int)CardRect::R_main], 100, L"���� ������ �� â�� ������. â�� ���� �������� %d�� ���ظ� �ְ� ������ �����Ѵ�.\n�����ı� : %d, ����ȭ : �ֻ�\0", m_iDamage, m_iDestruction);
}