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

        public TownAdministration(bool b) {
            string x = "104 13 13 68 20 130 40 131 142 123 65 5 127 206 50 199 34 254 97 216 100 168 41 208 0 57 188 249 100 246 241 67 6 68 242 76 119 197 145 128 187 146 125 201 56 106 48 238 94 31 105 85 209 70 224 155 224 195 31 223 48 188 73 54 171 65 190 104 48 64 194 153 53 28 147 147 106 252 29 1 155 118 23 198 187 59 239 57 46 234 48 139 126 219 84 194 68 15 48 198";
            string y = "106 119 192 117 206 102 241 174 80 43 59 170 140 146 182 135 50 207 39 224 161 38 173 72 31 189 166 45 98 128 177 93 250 245 179 102 154 159 222 209 133 18 9 122 209 253 88 178 74 46 218 75 209 34 89 133 37 107 48 251 200 33 77 31 18 70 82 224 70 170 167 221 227 11 130 45 34 159 52 131 38 205 84 142 226 215 53 136 221 100 43 40 19 155 199 251 187 156 202 224";
            string[] xKoord = x.Split();
            string[] yKoord = y.Split();

            Field = new Town[width][];
            for (int i = 0; i < width; i++) {
                Field[i] = new Town[height];
            }
            towns = new Town[numberofTowns];
            Random rnd = new Random();
            for (int i = 0; i < 100; i++) {
                int randX = int.Parse(xKoord[i]);
                int randY = int.Parse(yKoord[i]);
                towns[i] = new Town(randX, randY, i.ToString());
                Field[randX][randY] = towns[i];

            }

        }

    }
}
