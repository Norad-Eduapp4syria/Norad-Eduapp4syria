﻿namespace EA4S.Scanner
{
	public class ScannerIntroductionState : IGameState
	{
		ScannerGame game;

		float timer = 2f;
		public ScannerIntroductionState(ScannerGame game)
		{
			this.game = game;
		}

		public void EnterState()
		{
            AudioManager.I.PlayDialog(Db.LocalizationDataId.Scanner_Title);
        }

		public void ExitState()
		{
            AudioManager.I.PlayDialog(Db.LocalizationDataId.Scanner_Intro);
        }

		public void Update(float delta)
		{
			timer -= delta;

			if (timer < 0)
			{
				game.SetCurrentState(game.PlayState);
				return;
			}
		}

		public void UpdatePhysics(float delta)
		{
		}
	}
}
