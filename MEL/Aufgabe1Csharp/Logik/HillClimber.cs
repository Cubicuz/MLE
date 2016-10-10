using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Aufgabe1Csharp.Logik {
    class HillClimber {
        protected double [][] distanceMatrix;
        protected int[] townRef;


        private TownAdministration townAdministation;

        public HillClimber(ref TownAdministration ta) {
            townAdministation = ta;

            //save all distances in a Matrix so they are only calculated once
            distanceMatrix = new double[townAdministation.numberofTowns][];
            for (int i = 0; i < ta.numberofTowns; i++) {
                distanceMatrix[i] = new double[townAdministation.numberofTowns];
            }

            for (int i = 0; i < townAdministation.numberofTowns; i++) {
                for (int j = i; j < townAdministation.numberofTowns; j++) {
                    if (i != j) {
                        distanceMatrix[i][j] = distanceMatrix[j][i] = Math.Sqrt(Math.Pow(townAdministation.towns[i].x - townAdministation.towns[j].x, 2) + Math.Pow(townAdministation.towns[i].y - townAdministation.towns[j].y,2));
                    }
                }
            }
            townRef = new int[townAdministation.numberofTowns];
            for (int i = 0; i<townAdministation.numberofTowns; i++) {
                townRef[i] = i;
            }
        }

        private void swap(int i, int j) {
            int s = townRef[i];
            townRef[i] = townRef[j];
            townRef[j] = s;
        }

        private double fitness() {
            double length = 0;
            int towns1 = townRef.Length - 1;
            for (int i = 0; i< towns1; i++) {
                length += distanceMatrix[townRef[i]][townRef[i+1]];
            }
            length += distanceMatrix[townRef[0]][townRef[towns1]];
            return length;
        }

        private bool isSwapBetter(int i, int j) {
            double lengthOld, lengthNew;
            lengthOld = distanceMatrix[townRef[i - 1]][townRef[i]] + distanceMatrix[townRef[i + 1]][townRef[i]] + distanceMatrix[townRef[j - 1]][townRef[j]] + distanceMatrix[townRef[j + 1]][townRef[j]];
            lengthNew = distanceMatrix[townRef[i - 1]][townRef[j]] + distanceMatrix[townRef[i + 1]][townRef[j]] + distanceMatrix[townRef[j - 1]][townRef[i]] + distanceMatrix[townRef[j + 1]][townRef[i]];
            return lengthNew < lengthOld;
        }

        public void HillClimb() {
            int rounds = 0, swapi, swapj;
            int maxRounds = 10000;
            int townCount = townRef.Length;
            double length = fitness();
            Random r = new Random();
            while (rounds < maxRounds) {
                rounds++;
                swapi = r.Next(0, townCount);
                do {
                    swapj = r.Next(0, townCount);
                } while (swapj == swapi);
                if (isSwapBetter(swapi, swapj)) {
                    swap(swapi, swapj);
                    Console.WriteLine("new Length: " + length);
                }
            }
            for (int i = 0; i < townCount; i++) {
                System.Console.WriteLine(townAdministation.towns[townRef[i]].name);
            }
        }

    }
}
