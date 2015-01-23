////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TICTACTOELOGIC_H__
#define __GUI_TICTACTOELOGIC_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Application logic for Tic Tac Toe demo game
////////////////////////////////////////////////////////////////////////////////////////////////////
class TicTacToeLogic: public Noesis::BaseComponent
{
public:
    TicTacToeLogic(Noesis::FrameworkElement* uiRoot);
    ~TicTacToeLogic();

private:
    void BoardClicked(Noesis::BaseComponent* sender,
        const Noesis::MouseButtonEventArgs& args);

    void CellChecked(Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& args);

    void WinAnimationCompleted(Noesis::BaseComponent* sender,
        const Noesis::TimelineEventArgs& args);
    void TieAnimationCompleted(Noesis::BaseComponent* sender,
        const Noesis::TimelineEventArgs& args);
    void ResetAnimationCompleted(Noesis::BaseComponent* sender,
        const Noesis::TimelineEventArgs& args);
    void ProgressFadeAnimationCompleted(Noesis::BaseComponent* sender,
        const Noesis::TimelineEventArgs& args);
    void ScoreHalfAnimationCompleted(Noesis::BaseComponent* sender,
        const Noesis::TimelineEventArgs& args);
    void StatusHalfAnimationCompleted(Noesis::BaseComponent* sender,
        const Noesis::TimelineEventArgs& args);

    NsSymbol GetPlayerState() const;

    void StartGame();
    void WinGame(const NsString& winPlay);
    void TieGame();
    void SwitchPlayer();

    struct Cell;
    void MarkCell(Cell& cell);

    void UpdateScoreAnimation(const NsChar* targetName);

    NsBool HasWon(NsString& winPlay);
    NsBool HasTied();

    NsBool PlayerCheckedRow(NsSymbol player, NsSize row) const;
    NsBool PlayerCheckedCol(NsSymbol player, NsSize col) const;
    NsBool PlayerCheckedDiag(NsSymbol player, NsSize start, NsSize end) const;
    NsBool PlayerCheckedCell(NsSymbol player, NsSize row, NsSize col) const;

private:
    Noesis::FrameworkElement* mRoot;
    Noesis::FrameworkElement* mBoardPanel;
    Noesis::TextBlock* mStatusText;

    Noesis::TextBlock* mScorePlayer1Text;
    Noesis::TextBlock* mScorePlayer2Text;
    Noesis::TextBlock* mScoreTiesText;
    Noesis::TextBlock* mScoreText;

    Noesis::Storyboard* mWinAnimation;
    Noesis::Storyboard* mTieAnimation;
    Noesis::Storyboard* mResetAnimation;
    Noesis::Storyboard* mProgressAnimation;
    Noesis::Storyboard* mProgressFadeAnimation;
    Noesis::Storyboard* mScoreHalfAnimation;
    Noesis::Storyboard* mScoreEndAnimation;
    Noesis::Storyboard* mStatusHalfAnimation;
    Noesis::Storyboard* mStatusEndAnimation;

    NsString mStatusMsg;

    NsSize mScorePlayer1;
    NsSize mScorePlayer2;
    NsSize mScoreTies;
    NsSize mScore;

    enum Player
    {
        Player_None,
        Player_1,
        Player_2
    };

    Player mPlayer;
    Player mLastStarterPlayer;

    struct Cell
    {
        NsSymbol player;
        Noesis::ToggleButton* btn;

        NsString ToString() const { return ""; }
        NsUInt32 GetHashCode() const { return 0; };
        void Serialize(Noesis::SerializationData* data) const {}
        void Unserialize(Noesis::UnserializationData* data) {}

        NS_IMPLEMENT_INLINE_REFLECTION_(Cell, Noesis::NoParent)
    };

    Cell mBoard[3][3];

    NS_DECLARE_REFLECTION(TicTacToeLogic, Noesis::BaseComponent)
};


#endif
