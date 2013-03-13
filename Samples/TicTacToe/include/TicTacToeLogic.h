////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TICTACTOELOGIC_H__
#define __GUI_TICTACTOELOGIC_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/String.h>
#include <NsCore/Symbol.h>


// Forward declarations
//@{
namespace Noesis
{
namespace Gui
{
class FrameworkElement;
class ToggleButton;
class TextBlock;
class Storyboard;
struct MouseButtonEventArgs;
struct RoutedEventArgs;
struct TimelineEventArgs;
}
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Application logic for Tic Tac Toe demo game
////////////////////////////////////////////////////////////////////////////////////////////////////
class TicTacToeLogic: public Noesis::Core::BaseComponent
{
public:
    TicTacToeLogic(Noesis::Gui::FrameworkElement* uiRoot);
    ~TicTacToeLogic();

private:
    void BoardClicked(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::MouseButtonEventArgs& args);

    void CellChecked(Noesis::Core::BaseComponent* sender, const Noesis::Gui::RoutedEventArgs& args);

    void WinAnimationCompleted(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::TimelineEventArgs& args);
    void TieAnimationCompleted(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::TimelineEventArgs& args);
    void ResetAnimationCompleted(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::TimelineEventArgs& args);
    void ProgressFadeAnimationCompleted(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::TimelineEventArgs& args);
    void ScoreHalfAnimationCompleted(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::TimelineEventArgs& args);
    void StatusHalfAnimationCompleted(Noesis::Core::BaseComponent* sender,
        const Noesis::Gui::TimelineEventArgs& args);

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
    Noesis::Gui::FrameworkElement* mRoot;
    Noesis::Gui::FrameworkElement* mBoardPanel;
    Noesis::Gui::TextBlock* mStatusText;

    Noesis::Gui::TextBlock* mScorePlayer1Text;
    Noesis::Gui::TextBlock* mScorePlayer2Text;
    Noesis::Gui::TextBlock* mScoreTiesText;
    Noesis::Gui::TextBlock* mScoreText;

    Noesis::Gui::Storyboard* mWinAnimation;
    Noesis::Gui::Storyboard* mTieAnimation;
    Noesis::Gui::Storyboard* mResetAnimation;
    Noesis::Gui::Storyboard* mProgressAnimation;
    Noesis::Gui::Storyboard* mProgressFadeAnimation;
    Noesis::Gui::Storyboard* mScoreHalfAnimation;
    Noesis::Gui::Storyboard* mScoreEndAnimation;
    Noesis::Gui::Storyboard* mStatusHalfAnimation;
    Noesis::Gui::Storyboard* mStatusEndAnimation;

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
        Noesis::Gui::ToggleButton* btn;

        NS_IMPLEMENT_INLINE_REFLECTION_(Cell, Noesis::Core::NoParent)
    };

    Cell mBoard[3][3];

    NS_DECLARE_REFLECTION(TicTacToeLogic, Noesis::Core::BaseComponent)
};


#endif
