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

        private double isSwapBetter(int i, int j) {
            double lengthOld, lengthNew;
            int ibefore = i - 1;
            int iafter = i + 1;
            int jbefore = j - 1;
            int jafter = j + 1;
            if (i == 0)
                ibefore = 99;
            if (i == 99)
                iafter = 0;
            if (j == 0)
                jbefore = 99;
            if (j == 99)
                jafter = 0;
            if (i - j == 1) {
                lengthOld = distanceMatrix[townRef[jbefore]][townRef[j]] + distanceMatrix[townRef[i]][townRef[iafter]];
                lengthNew = distanceMatrix[townRef[jbefore]][townRef[i]] + distanceMatrix[townRef[j]][townRef[iafter]];
            } else if (j - i == 1) {
                lengthOld = distanceMatrix[townRef[ibefore]][townRef[i]] + distanceMatrix[townRef[j]][townRef[jafter]];
                lengthNew = distanceMatrix[townRef[ibefore]][townRef[j]] + distanceMatrix[townRef[i]][townRef[jafter]];
            } else if (((i == 99) && (j == 0)) || ((i == 0) && (j == 99))) {
                lengthOld = distanceMatrix[townRef[1]][townRef[0]] + distanceMatrix[townRef[99]][townRef[98]];
                lengthNew = distanceMatrix[townRef[1]][townRef[99]] + distanceMatrix[townRef[0]][townRef[98]];
            } else {
                lengthOld = distanceMatrix[townRef[ibefore]][townRef[i]] + distanceMatrix[townRef[iafter]][townRef[i]] + distanceMatrix[townRef[jbefore]][townRef[j]] + distanceMatrix[townRef[jafter]][townRef[j]];
                lengthNew = distanceMatrix[townRef[ibefore]][townRef[j]] + distanceMatrix[townRef[iafter]][townRef[j]] + distanceMatrix[townRef[jbefore]][townRef[i]] + distanceMatrix[townRef[jafter]][townRef[i]];
            }
            return lengthOld - lengthNew;
        }

        public double HillClimb(int rounds = 10000) {
            int swapi, swapj;
            int maxRounds = 10000000;
            int townCount = townRef.Length;
            double length = fitness();
            Random r = new Random();
            while (rounds < maxRounds) {
                rounds++;
                swapi = r.Next(0, townCount);
                do {
                    swapj = r.Next(0, townCount);
                } while (swapj == swapi);
                if (isSwapBetter(swapi, swapj) > 0) {
                    swap(swapi, swapj);
                }
            }
            return fitness();
        }

        public double SimulatedAnnealing(double temperature, double epsilon) {
            int swapi, swapj;

            int townCount = townRef.Length;
            double lastFitness = fitness(), fitnesDiff = 0, wahrscheinlichkeit;
            Random r = new Random();
            do {

                swapi = r.Next(0, townCount);
                do {
                    swapj = r.Next(0, townCount);
                } while (swapi == swapj);

                fitnesDiff = isSwapBetter(swapi, swapj);
                wahrscheinlichkeit = Math.Exp((fitnesDiff) / temperature);
                if ((fitnesDiff > 0) || (r.Next(0, 1000) < wahrscheinlichkeit * 1000)) {
                    swap(swapi, swapj);
                    if (fitnesDiff <= 0) {
                        Console.WriteLine("Rückschritt wahrscheinlichkeit: " + wahrscheinlichkeit);
                    }
                }
                temperature -= epsilon;
            } while (temperature > epsilon);
            return fitness();
        }

        public void Resett() {
            for (int i = 0;i < 100; i++) {
                townRef[i] = i;
            }
        }
    }
}
