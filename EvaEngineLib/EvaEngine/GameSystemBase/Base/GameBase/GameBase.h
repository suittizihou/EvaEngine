#pragma once

namespace EvaEngine {
	/// <summary>
	/// いわゆるエントリーポイントのようなクラス。Initをオーバーロードしてシーンを登録したりするのに使う。
	/// </summary>
	class GameBase {
	public:
		GameBase(const unsigned int windowWidth, const unsigned int windowHeight);
		~GameBase();

		/// <summary>
		/// ゲーム開始時にやっておきたい初期化処理とかをオーバーロードして書く
		/// </summary>
		virtual void Init() = 0;

		static GameBase* Instance();

	private:
		static GameBase* m_GameBase;
	};
}