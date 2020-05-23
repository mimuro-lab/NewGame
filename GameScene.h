
/*!
@file GameScene.h
@brief GameSceneクラスが定義されているヘッダファイル
@date 2020/04/16/19:55
@author mimuro
*/

#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include "AbstractScene.h"
#include "Controller.h"
#include "SelectWindow.h"
#include "ImagePath_Unitychan.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Bullet.h"

using namespace std;

/*!
@class GameScene
@brief SystemLooperクラスで生成されるシーンクラスの一つでAbstractSceneを継承する。ゲーム画面を担当する。
@date 2020/04/16/19:56
@author mimuro
*/
class GameScene :
	public AbstractScene,
	private SelectWindow
{
	//! 背景のStageの処理を行うオブジェクト
	shared_ptr<Stage> stage;

	//! Playerの処理をになうオブジェクト
	shared_ptr<Player> player;

	shared_ptr<Enemy> enemy;

	shared_ptr<Enemy> enemy1;

	//! 画面上のダメージ要素
	vector<shared_ptr<Bullet>> damageObjs;

public:
	//! コンストラクタ呼び出し時にshared_ptr<ISceneChanger>型のオブジェクトを受け取り、親のAbstractSceneクラスのコンストラクタに代入する。
	GameScene(shared_ptr<ISceneChanger> _changer) :
		AbstractScene(_changer),
		SelectWindow(_changer),
		stage(make_shared<Stage>(Define::blockWidth, Define::blockHeight)),
		player(make_shared<Player>(stage))

	{
		enemy = make_shared<Enemy>(stage, 100,100);
		enemy1 = make_shared<Enemy>(stage, 150, 100);

	};
	~GameScene() = default;

	//! ゲーム画面に必要な前処理を行う関数。
	void update() override;

	//! ゲーム画面の描画を行う関数。
	void draw() override;
};

