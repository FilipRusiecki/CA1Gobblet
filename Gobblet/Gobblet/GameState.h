#pragma once
/// <summary>
/// the enum class should be used to change gamestates when playing with the ai
/// </summary>
enum class GameState
{
    getPiece,
    isGameOver,
    getPossibleMoves,
    getCurrentPlayer,
    isMoveValid,
    gamePlaying
};
