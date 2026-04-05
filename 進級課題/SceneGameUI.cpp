#include "SceneGameUI.h"
#include "Player.h"
#include "DxLib.h"

SceneGameUI::SceneGameUI(const Player* player) :
	m_player(player),
	m_fontHandle(0),
	m_hpPos(30, 20),		// HPの表示位置
	m_expPos(10, 50),		// EXPの表示位置
	m_levelPos(10, 90)		// レベルの表示位置
{
	m_transform.position = Screen::TopLeft; // フォントの描画基準点を画面の左上に設定
	
}

void SceneGameUI::Load()
{
	m_fontHandle = CreateFontToHandle("Resource/PixelMplus/PixelMplus12-Regular.ttf", 40, 3);
}

void SceneGameUI::Release()
{
	DeleteFontToHandle(m_fontHandle);
}

void SceneGameUI::Update()
{
	// UIは特に更新することがないので空
}

void SceneGameUI::Draw()
{
	// プレイヤーのHPを描画
	std::string hpText = "HP: " + std::to_string(m_player->m_status.GetHp()) + "/" + std::to_string(m_player->m_status.GetMaxHp());
	DrawStringToHandle(static_cast<int>(m_transform.position.x + m_hpPos.x), static_cast<int>(m_transform.position.y + m_hpPos.y), hpText.c_str(), GetColor(0, 255, 0), m_fontHandle);
}

