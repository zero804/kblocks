/***************************************************************************
*   KBlocks, a falling blocks game by KDE                                *
*   Copyright (C) 2010 Mauricio Piacentini <mauricio@tabuleiro.com>       *
*                      Zhongjie Cai <squall.leonhart.cai@gmail.com>       *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/
#ifndef KBLOCKSSCENE_H
#define KBLOCKSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QString>

#include <KGamePopupItem>

#include "KBlocksSound.h"
#include "KBlocksGraphics.h"
#include "KBlocksItemGroup.h"
#include "KBlocksScore.h"

#include "GameLogicInterface.h"

#include "KBlocksDefine.h"

class KBlocksScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit KBlocksScene(GameLogicInterface *p, int capacity = 1);
    ~KBlocksScene();

    KBlocksItemGroup *getItemGroup(int index);
    KBlocksScore *getScoreHandler(int index);

    void createGameItemGroups(int groupCount, bool snapshotMode = false);
    void deleteGameItemGroups();

    void setGamesPerLine(int count);
    void setGameAnimEnabled(bool flag);
    void setWaitForAllUpdate(bool flag);
    void setUpdateInterval(int interval);
    void setSoundsEnabled(bool enabled);

    void readSettings(const QSize &viewSize);
    void viewScaled(const QSize &newsize);

    void startGame();
    void stopGame();

    void pauseGame(bool flag, bool fromUI = false);

    void addScore(int gameIndex, int lineCount);

signals:
    void scoreChanged(int index, int points, int lines, int level);
    void isHighscore(int index, int points, int level);

private:
    void updateDimensions();

private slots:
    void greetPlayer();
    void gameOverPlayer();
    void gameOverMultiWin();
    void gameOverMultiLose();

    void showMessage(const QString &message, int ms);

    void updateGame();
    void readyForAction(int groupID);

public slots:
    void playMoveSound();
    void playDropSound();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    GameLogicInterface *mpGameLogic = nullptr;
    bool mGameStarted;

    KBlocksGraphics *mpGrafx = nullptr;
    KBlocksSound *mpSnd = nullptr;

    int mSceneGamesPerLine;
    bool mGameAnimEnabled;
    bool mWaitForAllUpdate;
    bool *maGameReadySignal = nullptr;

    bool mSnapshotMode;

    int mTopGameLevel;

    int mMaxCapacity;
    int mGroupCount;
    KBlocksItemGroup **maGroupList = nullptr;
    KBlocksScore **maGameScoreList = nullptr;

    KGamePopupItem *mMessageBox = nullptr;

    int mUpdateInterval;
    QTimer mUpdateTimer;
};

#endif

