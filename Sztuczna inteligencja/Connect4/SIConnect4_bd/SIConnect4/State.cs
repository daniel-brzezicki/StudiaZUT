﻿/************************************************************************
 * AISearch - Small search library written in c#
 * Copyright (C) 2020 Marcin Pietrzykowski (mpietrzykowski@wi.zut.edu.pl)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***********************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AISearch {
    public abstract class State : IState {

        #region Private Fields

        /// <summary>
        /// Minimalna gwarantowana wygrana dla gracza maksymalizującego.
        /// </summary>
        private double alpha = double.NegativeInfinity;

        /// <summary>
        /// Maksymalna gwarantowana wygrana dla gracza minimalizującego.
        /// </summary>
        private double beta = Double.PositiveInfinity;

        #endregion //end Private Fields

        #region Protected Fields

        /// <summary>
        /// Dzieci
        /// </summary>
        protected List<IState> children = null;

        /// <summary>
        /// Głębokość stanu w drzewie
        /// </summary>
        protected double depth = 0.0;

        /// <summary>
        /// Koszt osiągnięcia bierzącego stanu ze stanu początkowego
        /// </summary>
        protected double g = 0.0;

        /// <summary>
        /// Ocena heurystyczna
        /// </summary>
        protected double h = 0.0;

        /// <summary>
        /// Definiuje czy wybrany stan jest dostępnu. W grach jak sudoku wybrany stan może być nie osiągalny.
        /// </summary>
        protected bool isAdmissible;

        /// <summary>
        /// Rodzic
        /// </summary>
        protected IState parent = null;

        /// <summary>
        /// Zwraca lub ustawia zazwę początkowego ruchu pozwalającego na dojście do tego stanu.
        /// </summary>
        protected String rootMove = null;

        #endregion //end Protected Fields

        #region Constructors

        /// <summary>
        /// Konstuktor tworzący nową instancje.
        /// </summary>
        /// <param name="parent">Rodzic stanu.</param>
        public State() {
            this.children = new List<IState>();
        }

        /// <summary>
        /// Konstuktor tworzący nową instancje.
        /// </summary>
        /// <param name="parent">Rodzic stanu.</param>
        public State(IState parent) : this() {
            this.parent = parent;
        }

        #endregion //end Constructors

        #region IState Members

        #region Properties

        /// <summary>
        /// Minimalna gwarantowana wygrana dla gracza maksymalizującego.
        /// </summary>
        public double Alpha {
            get {
                return this.alpha;
            }
            set {
                this.alpha = value;
            }
        }

        /// <summary>
        /// Maksymalna gwarantowana wygrana dla gracza minimalizującego.
        /// </summary>
        public double Beta {
            get {
                return this.beta;
            }
            set {
                this.beta = value;
            }
        }

        /// <summary>
        /// Zwraca i ustawia potomków danego stanu.
        /// </summary>
        public List<IState> Children {
            get {
                return this.children;
            }
            set {
                this.children = value;
            }
        }

        /// <summary>
        /// Zwraca lub ustawia głębokość stanu w drzwie.
        /// </summary>
        public double Depth {
            get {
                return this.depth;
            }
            set {
                this.depth = value;
            }
        }

        /// <summary>
        /// Zwraca f. f = g + h.
        /// </summary>
        public double F {
            get {
                return this.g + this.h;
            }
        }

        /// <summary>
        /// Zwraca i ustawia g - koszt osiągnięca wybranego stanu.
        /// </summary>
        public double G {
            get {
                return this.g;
            }
            set {
                this.g = value;
            }
        }

        /// <summary>
        /// Zwraca h - heurystyczną wartość dla stanu
        /// </summary>
        public double H {
            get {
                return this.h;
            }
            set {
                this.h = value;
            }
        }

        /// <summary>
        /// Nazwa statnu jednoznacznie go identyfikująca. 
        /// </summary>
        public abstract string ID {
            get;
        }

        /// <summary>
        /// Definiuje czy wybrany stan jest dostępnu. W grach jak sudoku wybrany stan może być nie osiągalny.
        /// </summary>
        public bool IsAdmissible {
            get { return this.isAdmissible; }
        }

        /// <summary>
        /// Zwraca i ustawia przodka danego stanu.
        /// </summary>
        public IState Parent {
            get {
                return this.parent;
            }
            set {
                this.parent = value;
            }
        }

        /// <summary>
        /// Zwraca lub ustawia zazwę początkowego ruchu pozwalającego na dojście do tego stanu.
        /// </summary>
        public string RootMove {
            get {
                return this.rootMove;
            }
            set {
                this.rootMove = value;
            }
        }

        #endregion //end Properties

        #region Methods

        /// <summary>
        /// Oblicza h - heurystyczną wartość dla danego stanu.
        /// </summary>
        /// <returns>Heurystyczna wartość.</returns>
        public abstract double ComputeHeuristicGrade();

        #endregion //end Methods

        #endregion //end IState Members
    }
}
