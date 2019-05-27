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
#include "KBlocksAnimDrop.h"

KBlocksAnimDrop::KBlocksAnimDrop(const QList<KBlocksSvgItem *> &items, int duration, QTimeLine::Direction direction)
{
    mItemList = items;

    mpTimeLine = new QTimeLine(duration);
    mpTimeLine->setFrameRange(0, 30);
    mpTimeLine->setDirection(direction);

    connect(mpTimeLine, &QTimeLine::valueChanged, this, &KBlocksAnimDrop::valueChanged);
    connect(mpTimeLine, &QTimeLine::finished, this, &KBlocksAnimDrop::endAnimation);

    mpTimeLine->start();
}

KBlocksAnimDrop::~KBlocksAnimDrop()
{
    delete mpTimeLine;
}

void KBlocksAnimDrop::valueChanged(qreal value)
{
    Q_UNUSED(value);
    for (KBlocksSvgItem *pItem : qAsConst(mItemList)) {
        pItem->execPosAnim(value);
    }
}

void KBlocksAnimDrop::endAnimation()
{
    emit animationFinished();
}
