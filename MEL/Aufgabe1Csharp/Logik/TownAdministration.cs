using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Aufgabe1Csharp.Logik {
    class TownAdministration {
        public int width = 255;
        public int height = 255;
        public int numberofTowns = 100;

        public Town[] towns;
        public Town[][] Field;

        public TownAdministration() {
            Field = new Town[width][];
            for (int i = 0; i < width; i++) {
                Field[i] = new Town[height];
            }
            towns = new Town[numberofTowns];
            Random rnd = new Random();
            for (int i = 0; i < 100; i++) {
                int randX;
                int randY;
                do {
                    randX = rnd.Next(0, width);
                    randY = rnd.Next(0, height);
                } while (Field[randX][randY] != null);
                towns[i] = new Town(randX, randY, i.ToString());
                Field[randX][randY] = towns[i];
            }
        }

        public TownAdministration(string FilePath) {
            StreamReader inFile = new StreamReader(FilePath);
            string firstLine = inFile.ReadLine();
            //TODO: firstline auswerten
            Field = new Town[width][];
            for (int j = 0; j < width; j++) {
                Field[j] = new Town[height];
            }
            towns = new Town[numberofTowns];

            String [] line;
            int i = 0, x, y;
            while (!inFile.EndOfStream) {
                line = inFile.ReadLine().Split();
                x = int.Parse(line[0]);
                y = int.Parse(line[1]);
                towns[i] = new Town(x, y, line[0]);
                Field[x][y] = towns[i];
                i++;
            }
            inFile.Close();
            if (i != numberofTowns) {
                throw new Exception("falsche stadtzahl");
            }
        }

    }
}
