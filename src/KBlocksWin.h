/***************************************************************************
*   KBlocks, a falling blocks game by KDE                                *
*   Copyright (C) 2009 Mauricio Piacentini <mauricio@tabuleiro.com>       *
*                      Zhongjie Cai <squall.leonhart.cai@gmail.com>       *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/
#ifndef KBLOCKSWIN_H
#define KBLOCKSWIN_H

#include <KXmlGuiWindow>

#include "KBlocksScene.h"
#include "KBlocksView.h"

#include "KBlocksKeyboardPlayer.h"
#include "AI/KBlocksAIPlayer.h"

#include "KBlocksGameLogic.h"
#include "KBlocksPlayManager.h"
class QLabel;
class KBlocksWin : public KXmlGuiWindow
{
    Q_OBJECT

public:
    KBlocksWin(KBlocksGameLogic *p, KBlocksPlayManager *pM, int capacity, int gamecount);
    ~KBlocksWin();

public:
    void setGamesPerLine(int count);
    void setGameAnimEnabled(bool flag);
    void setWaitForAllUpdate(bool flag);
    void setUpdateInterval(int interval);

    void addScore(int gameIndex, int lineCount);

private slots:
    void startGame();
    void stopGame();
    void pauseGame();

    void singleGame();
    void pveStepGame();

    void focusEvent(bool flag);

    void configureSettings();
    void showHighscore();
    void onScoreChanged(int index, int points, int lines, int level);
    void onIsHighscore(int index, int points, int level);
    void onAllGamesStopped();
    void levelChanged();
    void setSoundsEnabled(bool enabled);

private:
    void setupGUILayout();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    int mMaxGameCapacity;
    int mGameCount;

    bool mGameAnim;
    bool mWaitForAll;

    KBlocksScene *mpGameScene = nullptr;
    KBlocksView  *mpGameView = nullptr;

    KBlocksGameLogic *mpGameLogic = nullptr;
    KBlocksPlayManager *mpPlayManager = nullptr;

    KBlocksKeyboardPlayer *mpKBPlayer = nullptr;
    KBlocksAIPlayer *mpAIPlayer = nullptr;

    QAction *m_pauseAction = nullptr;
    QLabel *mScore = nullptr;
};

#endif
