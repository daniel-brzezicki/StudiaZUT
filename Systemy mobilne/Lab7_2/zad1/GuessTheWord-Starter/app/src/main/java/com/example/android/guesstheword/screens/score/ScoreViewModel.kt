package com.example.android.guesstheword.screens.score

import android.util.Log

class ScoreViewModel(finalScore: Int) {
    var score = finalScore
    init {
        Log.i("ScoreViewModel", "Final score is $finalScore")
    }
}