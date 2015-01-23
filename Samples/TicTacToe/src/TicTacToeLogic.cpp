////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "TicTacToeLogic.h"

#include <assert.h>


using namespace Noesis;


NS_DECLARE_SYMBOL(Player1)
NS_DECLARE_SYMBOL(Player2)


#undef FindResource


////////////////////////////////////////////////////////////////////////////////////////////////////
TicTacToeLogic::TicTacToeLogic(Noesis::FrameworkElement* uiRoot): mRoot(uiRoot)
{
    assert(mRoot);

    mBoardPanel = mRoot->FindName<FrameworkElement>("Board");
    assert(mBoardPanel);
    mBoardPanel->MouseLeftButtonDown() += MakeDelegate(this, &TicTacToeLogic::BoardClicked);

    for (NsSize row = 0; row < 3; ++row)
    {
        for (NsSize col = 0; col < 3; ++col)
        {
            NsString cellName = NsString::Format("Cell%u%u", row, col);

            ToggleButton* btn = mRoot->FindName<ToggleButton>(cellName.c_str());
            assert(btn);

            Cell& cell = mBoard[row][col];
            cell.btn = btn;

            Ptr<BoxedValue> boxedCell = Boxing::Box<Cell*>(&cell);
            btn->SetTag(boxedCell.GetPtr());
            btn->SetIsEnabled(false);
            btn->Checked() += MakeDelegate(this, &TicTacToeLogic::CellChecked);
        }
    }

    mStatusText = mRoot->FindName<TextBlock>("StatusText");
    assert(mStatusText);

    mScorePlayer1Text = mRoot->FindName<TextBlock>("ScorePlayer1");
    assert(mScorePlayer1Text);

    mScorePlayer2Text = mRoot->FindName<TextBlock>("ScorePlayer2");
    assert(mScorePlayer2Text);

    mScoreTiesText = mRoot->FindName<TextBlock>("ScoreTies");
    assert(mScoreTiesText);

    mScoreText = 0;

    Ptr<ResourceKeyString> key;

    key = ResourceKeyString::Create("WinAnim");
    mWinAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());
    mWinAnimation->Completed() += MakeDelegate(this, &TicTacToeLogic::WinAnimationCompleted);

    key = ResourceKeyString::Create("TieAnim");
    mTieAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());
    mTieAnimation->Completed() += MakeDelegate(this, &TicTacToeLogic::TieAnimationCompleted);

    key = ResourceKeyString::Create("ResetAnim");
    mResetAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());
    mResetAnimation->Completed() += MakeDelegate(this, &TicTacToeLogic::ResetAnimationCompleted);

    key = ResourceKeyString::Create("ProgressAnim");
    mProgressAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());

    key = ResourceKeyString::Create("ProgressFadeAnim");
    mProgressFadeAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());
    mProgressFadeAnimation->Completed() += MakeDelegate(this,
        &TicTacToeLogic::ProgressFadeAnimationCompleted);

    key = ResourceKeyString::Create("ScoreHalfAnim");
    mScoreHalfAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());
    mScoreHalfAnimation->Completed() += MakeDelegate(this,
        &TicTacToeLogic::ScoreHalfAnimationCompleted);

    key = ResourceKeyString::Create("ScoreEndAnim");
    mScoreEndAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());

    key = ResourceKeyString::Create("StatusHalfAnim");
    mStatusHalfAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());
    mStatusHalfAnimation->Completed() += MakeDelegate(this,
        &TicTacToeLogic::StatusHalfAnimationCompleted);

    key = ResourceKeyString::Create("StatusEndAnim");
    mStatusEndAnimation = mRoot->FindResource<Storyboard>(key.GetPtr());

    mStatusText->SetText("Player 1 Turn");
    mPlayer = Player_1;
    mLastStarterPlayer = Player_1;
    mScorePlayer1 = 0;
    mScorePlayer2 = 0;
    mScoreTies = 0;
    mScore = 0;

    StartGame();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TicTacToeLogic::~TicTacToeLogic()
{
    for (NsSize row = 0; row < 3; ++row)
    {
        for (NsSize col = 0; col < 3; ++col)
        {
            mBoard[row][col].btn->Checked() -= MakeDelegate(this, &TicTacToeLogic::CellChecked);
        }
    }

    mBoardPanel->MouseLeftButtonDown() -= MakeDelegate(this, &TicTacToeLogic::BoardClicked);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::BoardClicked(BaseComponent* sender, const MouseButtonEventArgs& e)
{
    if (mPlayer == Player_None)
    {
        if (mLastStarterPlayer == Player_1)
        {
            mPlayer = Player_2;
            mLastStarterPlayer = Player_2;
            mStatusMsg = "Player 2 Turn";
        }
        else
        {
            mPlayer = Player_1;
            mLastStarterPlayer = Player_1;
            mStatusMsg = "Player 1 Turn";
        }

        mResetAnimation->Begin(mRoot);
        mStatusHalfAnimation->Begin(mRoot);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::CellChecked(BaseComponent* sender, const RoutedEventArgs& e)
{
    ToggleButton* btn = NsStaticCast<ToggleButton*>(sender);
    Cell& cell = *Boxing::Unbox<Cell*>(btn->GetTag());

    MarkCell(cell);

    NsString winPlay;
    if (HasWon(winPlay))
    {
        WinGame(winPlay);
    }
    else if (HasTied())
    {
        TieGame();
    }
    else
    {
        SwitchPlayer();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::WinAnimationCompleted(BaseComponent* sender, const TimelineEventArgs& args)
{
    if (mPlayer == Player_1)
    {
        mScoreText = mScorePlayer1Text;
        mScore = ++mScorePlayer1;
        UpdateScoreAnimation("ScorePlayer1");
    }
    else
    {
        mScoreText = mScorePlayer2Text;
        mScore = ++mScorePlayer2;
        UpdateScoreAnimation("ScorePlayer2");
    }

    mPlayer = Player_None;

    mScoreHalfAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::TieAnimationCompleted(BaseComponent* sender, const TimelineEventArgs& args)
{
    mScoreText = mScoreTiesText;
    mScore = ++mScoreTies;
    UpdateScoreAnimation("ScoreTies");

    mPlayer = Player_None;

    mScoreHalfAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::ResetAnimationCompleted(BaseComponent* sender, const TimelineEventArgs& args)
{
    StartGame();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::ProgressFadeAnimationCompleted(BaseComponent* sender,
    const TimelineEventArgs& args)
{
    mProgressAnimation->Stop(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::ScoreHalfAnimationCompleted(BaseComponent* sender,
    const TimelineEventArgs& args)
{
    assert(mScoreText);
    assert(mScore > 0);
    mScoreText->SetText(NsString::Format("%u", mScore).c_str());
    mScoreEndAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::StatusHalfAnimationCompleted(BaseComponent* sender,
    const TimelineEventArgs& args)
{
    assert(!mStatusMsg.empty());
    mStatusText->SetText(mStatusMsg.c_str());
    mStatusEndAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsSymbol TicTacToeLogic::GetPlayerState() const
{
    return mPlayer == Player_1 ? NSS(Player1) : NSS(Player2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::StartGame()
{
    NsSymbol player = GetPlayerState();

    PlaneProjection* projection = NsStaticCast<PlaneProjection*>(mBoardPanel->GetProjection());
    projection->ClearAnimation<NsFloat32>(PlaneProjection::RotationYProperty);
    CompositeTransform* t = NsStaticCast<CompositeTransform*>(mBoardPanel->GetRenderTransform());
    t->ClearAnimation<NsFloat32>(CompositeTransform::ScaleXProperty);
    t->ClearAnimation<NsFloat32>(CompositeTransform::ScaleYProperty);

    for (NsSize row = 0; row < 3; ++row)
    {
        for (NsSize col = 0; col < 3; ++col)
        {
            Cell& cell = mBoard[row][col];

            cell.player = NsSymbol::Null();
            cell.btn->ClearAnimation<NsFloat32>(UIElement::OpacityProperty);
            cell.btn->SetIsEnabled(true);
            cell.btn->SetIsChecked(false);
            VisualStateManager::GoToState(cell.btn, player, false);
        }
    }

    mProgressAnimation->Begin(mRoot, mRoot, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::WinGame(const NsString& winPlay)
{
    for (NsSize row = 0; row < 3; ++row)
    {
        for (NsSize col = 0; col < 3; ++col)
        {
            mBoard[row][col].btn->SetIsEnabled(false);
        }
    }

    mStatusMsg = NsString::Format("Player %d Wins", mPlayer == Player_1 ? 1 : 2);

    TimelineCollection* timelines = mWinAnimation->GetChildren();
    assert(timelines->Count() >= 3);

    DependencyObject* anim0 = NsStaticCast<DependencyObject*>(timelines->Get(0));
    Storyboard::SetTargetName(anim0, winPlay.c_str());

    DependencyObject* anim1 = NsStaticCast<DependencyObject*>(timelines->Get(1));
    Storyboard::SetTargetName(anim1, winPlay.c_str());

    DependencyObject* anim2 = NsStaticCast<DependencyObject*>(timelines->Get(2));
    Storyboard::SetTargetName(anim2, winPlay.c_str());

    mProgressFadeAnimation->Begin(mRoot);
    mWinAnimation->Begin(mRoot);
    mStatusHalfAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::TieGame()
{
    mStatusMsg = "Game Tied";

    mProgressFadeAnimation->Begin(mRoot);
    mTieAnimation->Begin(mRoot);
    mStatusHalfAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::SwitchPlayer()
{
    assert(mPlayer != Player_None);

    if (mPlayer == Player_1)
    {
        mPlayer = Player_2;
        mStatusMsg = "Player 2 Turn";
    }
    else
    {
        mPlayer = Player_1;
        mStatusMsg = "Player 1 Turn";
    }

    NsSymbol player = GetPlayerState();
    for (NsSize row = 0; row < 3; ++row)
    {
        for (NsSize col = 0; col < 3; ++col)
        {
            Cell& cell = mBoard[row][col];
            if (cell.player.IsNull())
            {
                VisualStateManager::GoToState(cell.btn, player, false);
            }
        }
    }

    mStatusHalfAnimation->Begin(mRoot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::MarkCell(Cell& cell)
{
    NsSymbol player = GetPlayerState();

    cell.player = player;
    cell.btn->SetIsEnabled(false);
    VisualStateManager::GoToState(cell.btn, player, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToeLogic::UpdateScoreAnimation(const NsChar* targetName)
{
    // Score Half
    TimelineCollection* timelines= mScoreHalfAnimation->GetChildren();
    assert(timelines->Count() == 1);

    DependencyObject* anim0 = NsStaticCast<DependencyObject*>(timelines->Get(0));
    Storyboard::SetTargetName(anim0, targetName);

    // Score End
    timelines = mScoreEndAnimation->GetChildren();
    assert(timelines->Count() == 3);

    anim0 = NsStaticCast<DependencyObject*>(timelines->Get(0));
    Storyboard::SetTargetName(anim0, targetName);

    DependencyObject* anim1 = NsStaticCast<DependencyObject*>(timelines->Get(1));
    Storyboard::SetTargetName(anim1, targetName);

    DependencyObject* anim2 = NsStaticCast<DependencyObject*>(timelines->Get(2));
    Storyboard::SetTargetName(anim2, targetName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TicTacToeLogic::HasWon(NsString& winPlay)
{
    NsSymbol player = GetPlayerState();

    for (NsSize i = 0; i < 3; ++i)
    {
        if (PlayerCheckedRow(player, i))
        {
            winPlay = NsString::Format("WinRow%u", i + 1);
            return true;
        }

        if (PlayerCheckedCol(player, i))
        {
            winPlay = NsString::Format("WinCol%u", i + 1);
            return true;
        }
    }

    if (PlayerCheckedDiag(player, 0, 2))
    {
        winPlay = "WinDiagLR";
        return true;
    }
    
    if (PlayerCheckedDiag(player, 2, 0))
    {
        winPlay = "WinDiagRL";
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TicTacToeLogic::HasTied()
{
    for (NsSize row = 0; row < 3; ++row)
    {
        for (NsSize col = 0; col < 3; ++col)
        {
            if (mBoard[row][col].player.IsNull())
            {
                return false;
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TicTacToeLogic::PlayerCheckedRow(NsSymbol player, NsSize row) const
{
    return PlayerCheckedCell(player, row, 0) && PlayerCheckedCell(player, row, 1) &&
        PlayerCheckedCell(player, row, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TicTacToeLogic::PlayerCheckedCol(NsSymbol player, NsSize col) const
{
    return PlayerCheckedCell(player, 0, col) && PlayerCheckedCell(player, 1, col) &&
        PlayerCheckedCell(player, 2, col);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TicTacToeLogic::PlayerCheckedDiag(NsSymbol player, NsSize start, NsSize end) const
{
    return PlayerCheckedCell(player, start, 0) && PlayerCheckedCell(player, 1, 1) &&
        PlayerCheckedCell(player, end, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool TicTacToeLogic::PlayerCheckedCell(NsSymbol player, NsSize row, NsSize col) const
{
    return mBoard[row][col].player == player;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_(TicTacToeLogic)