﻿

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Drawing2D;
using System.Drawing;
using System.Drawing.Imaging;

namespace RNAViewerNS
{
    //Notes:
    //These codes are mainly converted from AS(ActionScript used in flash),and to make it work,i build two 
    //class ArrayOfPoints and MyPoint which just act like interfaces.So,don't bother to understand these codes,
    //i even do not read it completely,either.
    class RNAViewer
    {
        //     Properties of Args:
        //          size:The length between two character.
        //          fontSize: The size of font,specified in pixel.
        //          spaceLen:The length from the end point of line to center of corresponding
        //                   character.(spaceLen a little bit smaller than fontSize is recommended,e.g.
        //                   fontSize=10,spaceLen=8.)
        //          basicLineColor:The color of line connected the consecutive characters.
        //          pairLineColor:The color of line between '1' and '1'.
        //          fontColor:The color of font.
        public class Args
        {
            public Args() { }
            public double size = 30;
            public double fontSize = 10;
            public double spaceLen = 8;
            public Color basicLineColor = Color.Green;
            public Color pairLineColor = Color.Red;
            public Color fontColor = Color.Blue;

        }
        private char[] seqs=" ".ToCharArray();
        private char[] matches = " ".ToCharArray();
        bool isTest = false;
        //**************basic function****************
        private void log(string mess)
        {
            //this is just used to output debug message...
            //Form1.log(mess);
        }
        private void testDraw(Graphics g)
        {
            log("this is a test...");
            double size = 50;
            int i;
            drawStr(g, "A", new MyPoint(size, size), (float)size * 2, Color.Black);
            ArrayOfPoints lines = new ArrayOfPoints();
            lines.push(new MyPoint(0, 0));
            lines.push(new MyPoint(size, 0));
            lines.push(new MyPoint(size, size));
            lines.push(new MyPoint(0, size));
            lines.push(new MyPoint(0, 0));

            for (i = 0; i < lines.Length - 1; i++)
            {
                drawLine(g, lines[i], lines[i + 1], Color.Red);
            }
            lines = arrayMulti(lines, 2);
            for (i = 0; i < lines.Length - 1; i++)
            {
                drawLine(g, lines[i], lines[i + 1], Color.Red);
            }
        }
        private void drawStr(Graphics g,String str, MyPoint p, float fontSize,Color fontColor)
        {
            MyPoint offset = new MyPoint((float)(-fontSize * 0.05), (float)(-fontSize * 0.17));
             g.DrawString(str, new Font("宋体", fontSize), new SolidBrush(fontColor),p.add(new MyPoint(-fontSize/2,-fontSize/2)).add(offset).toPointF());
         }
        private void drawLine(Graphics g,MyPoint from, MyPoint to, Color color)
        {
            g.DrawLine(new Pen(color), from.toPointF(), to.toPointF());
        }
        
        
        // Summary:
        //     Initializes the the seqs and matches.This must be called firstly!.
        //
        // Parameters:
        //   seqStr:
        //     The sequence inputed by user, e.g."AUGCAUGC"
        //   matchStr:
        //     The string generated by your progam which means the structure of RNA
        //
        // Returns:
        //     true if your seqStr and matchStr contain no errors,otherwise,false.
        //     That is to say if and only if the length of seqStr equals to matchStr and the
        //     number of '1' in matchStr is even, it return true.
        public bool init(string seqStr = "AUGCAUGC", string matchStr = "0100100110")
        {
            int numOne = 0;
            int i = 0;
            if (seqStr == "" || matchStr == "" || seqStr.Length <= 0 || seqStr.Length != matchStr.Length)
            {
                return false;
            }
            //
            int len = matchStr.Length;
            for (i = 0; i < len; i++)
            {
                if (matchStr.ElementAt(i) == '1') numOne++;
            }
            if (numOne % 2 != 0) return false;

            //all is ok,processing...
            seqs = seqStr.ToCharArray();
            matches = matchStr.ToCharArray();
            //
            log("all is ok");
            log("seqs:" + seqStr);
            log("matches:" + matchStr);
            string mess = "";
            string mess2 = "";
            for (i = 0; i < len; i++)
            {
                mess += seqs[i] + ",";
                mess2 += matches[i] + ",";
            }
            log("seq(arr):" + mess);
            log("match(arr):" + mess2);
            log("len:" + len);
            return true;
        }
        // Summary:
        //     Create and save the result as a file named fileName (of which the type is gif).
        //     This should be invoked after the init().
        //
        // Parameters:
        //   fileName:
        //     Just as it looks like,it is the name of file you want to save as.
        //
        //   args:
        //     A structure used to specify your own style image.Also,you can use a default 
        //     one without passing it.
        //     Properties of Args:
        //          size:The length between two character.
        //          fontSize: The size of font,specified in pixel.
        //          spaceLen:The length from the end point of line to center of corresponding
        //                   character.(spaceLen a little bit smaller than fontSize is recommended,e.g.
        //                   fontSize=10,spaceLen=8.)
        //          basicLineColor:The color of line connected the consecutive characters.
        //          pairLineColor:The color of line between '1' and '1'.
        //          fontColor:The color of font.
        public void create(string fileName, Args args=null)
        {
            if (args == null) args = new Args();
            //passing args....
            double size = args.size;
            double fontSize = args.fontSize;
            double spaceLen = args.spaceLen;
            Color basicLineColor = args.basicLineColor;
            Color pairLineColor = args.pairLineColor;
            Color fontColor = args.fontColor;
            //
            log("going...");
            //creating the original points base on seqs and matches
            ArrayOfPoints points = createPoints(seqs, matches);
            //generate the accurate drawPoints which will be draw on device from original points.
            ArrayOfPoints drawPoints = arrayMultiP(points, new MyPoint(size, -size));
            RectangleF rect = arrayGetRect(drawPoints);
            drawPoints = arrayAdd(drawPoints, new MyPoint(-rect.Left, -rect.Top));
            drawPoints = arrayAdd(drawPoints, new MyPoint(fontSize/2, fontSize/2));
            drawPoints.push(drawPoints[drawPoints.Length - 1]);
            //inflate the rect to contain all the graphics,and will be used as the size of bitmap.
            rect.Inflate((float)fontSize, (float)fontSize);
            //
            //create a bitmap and draw graph in it
            Bitmap bp;
            Graphics g;
            bp = new Bitmap((int)rect.Width, (int)rect.Height, PixelFormat.Format64bppArgb);
            g = Graphics.FromImage(bp);
            g.SmoothingMode = SmoothingMode.HighQuality;
            ///g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            //g.CompositingQuality = CompositingQuality.HighQuality;/**/
            g.Clear(Color.White);
            if(isTest){
                testDraw(g);
            }else{
                //now start drawing base on drawPoints,with argument specified by user.
                draw(g,drawPoints, spaceLen,(float)  fontSize,  basicLineColor,  pairLineColor,  fontColor);
            }
            
            //save the bitmap as fileName
            bp.Save(fileName, ImageFormat.Gif);
            bp.Dispose();
            g.Dispose();
        }
        private void draw(Graphics g, ArrayOfPoints drawPoints, double spaceLen, float fontSize, Color basicLineColor, Color pairLineColor, Color fontColor)
        {

            for (int i = 0; i < drawPoints.Length - 1; i++)
            {
                drawStr(g, seqs[i].ToString(), drawPoints[i], (float)fontSize, fontColor);
                ArrayOfPoints line = getCutLine(drawPoints[i], drawPoints[i + 1], spaceLen);
                drawLine(g, line[0], line[1], basicLineColor);
            }
            int l, r;
            l = -1; r = matches.Length;
            while (l < r)
            {
                //we assume the matches conatins double '1' (num>=0)
                l++;
                while (l < r && matches[l] != '1') l++;
                if (l == r) break;
                r--;
                while (matches[r] != '1') r--;
                ArrayOfPoints line = getCutLine(drawPoints[l], drawPoints[r], spaceLen);
                drawLine(g, line[0], line[1], pairLineColor);
            }
        }
        //************helpful math function*************
        private ArrayOfPoints createPoints(char[] seqs, char[] matches)
        {
            log("creating points....");
            ArrayOfPoints points = new ArrayOfPoints();
            int loopL = -1, loopR = -1;
            int tailL, tailR;
            int l, r;

            l = 0; r = matches.Length - 1;

            while (l < r && matches[l] != '1') l++;

            if (l < r)
            {
                log("contain both 1 and 0");

                while (l < r && matches[r] != '1') r--;

                tailL = l;
                tailR = r;
                //
                loopL = l;
                loopR = r;
                while (l < r)
                {
                    l++;
                    while (l < r && matches[l] != '1') l++;
                    if (l == r) break;
                    loopL = l;
                    r--;
                    while (matches[r] != '1') r--;

                }
                loopR = r;
                l = loopL;
                log("loopL:" + loopL);
                log("loopR:" + loopR);
                log("tailL:" + tailL);
                log("tailR:" + tailR);

                //
                arrayFill(createLoop(r - l + 1), points, l);
                log("len of loop:" + (r - l + 1));
                ArrayOfPoints leftPoints;
                ArrayOfPoints rightPoints;
                while (true)
                {
                    for (l = loopL - 1; l >= tailL; l--) if (matches[l] == '1') break;
                    for (r = loopR + 1; r <= tailR; r++) if (matches[r] == '1') break;
                    if (matches[l] != '1') break;
                    //
                    leftPoints = createSideLoop(loopL - l + 1);
                    leftPoints = arrayMultiP(leftPoints, new MyPoint(-1, 1));
                    rightPoints = createSideLoop(r - loopR + 1);
                    //
                    double heightL = arrayGetHeight(leftPoints);
                    double heightR = arrayGetHeight(rightPoints);
                    if (heightL < heightR) { leftPoints = arrayMultiP(leftPoints, new MyPoint(1, heightR / heightL)); }
                    else if (heightL > heightR) { rightPoints = arrayMultiP(rightPoints, new MyPoint(1, heightL / heightR)); }
                    //
                    arrayFill(arrayAdd(leftPoints, points[loopL]).reverse(), points, l);
                    arrayFill(arrayAdd(rightPoints, points[loopR]), points, loopR + 1);
                    //
                    loopL = l;
                    loopR = r;
                    if (loopR == tailR) break;
                }

                leftPoints = createLine(tailL + 1);
                leftPoints = arrayMultiP(leftPoints, new MyPoint(-1, 1));
                rightPoints = createLine(matches.Length - tailR);
                //
                arrayFill(arrayAdd(leftPoints, points[loopL]).reverse(), points, 0);
                arrayFill(arrayAdd(rightPoints, points[loopR]), points, tailR + 1);
                //
            }
            else
            {
                log("contain only 0");
                points[0] = new MyPoint(0, 0);
                arrayFill(createLine(matches.Length), points, 1);
            }
            log("created points:" + points);
            return points;
        }
        private ArrayOfPoints getCutLine(MyPoint from, MyPoint to, double cut)
        {
            ArrayOfPoints r = new ArrayOfPoints(2);
            MyPoint origin = from;
            MyPoint dir = to.sub(from);
            double len = dir.Length;
            if (len <= cut * 2)
            {
                r[0] = from;
                r[1] = from;
                return r;
            }
            dir = pointMulti(dir, 1 / len);
            from = origin.add(pointMulti(dir, cut));
            to = origin.add(pointMulti(dir, len - cut));
            //
            r[0]=from;
            r[1]=to;
            return r;
        }
        //
        private ArrayOfPoints createLoop(int num)
        {
            ArrayOfPoints a = new ArrayOfPoints();
            if (num < 2) { log("createLoop error num must >=2,now num:" + num);}
            double angle = (double)(num - 2) * Math.PI / (double)(num);
            //
            MyPoint p = new MyPoint(-1, 0);
            a.push(p);
            int i;
            for (i = 1; i < num; i++)
            {
                p = a[i - 1];
                a.push(rotateMyPoint(new MyPoint(-p.X, -p.Y), angle));
            }

            a[0] = new MyPoint(0, 0);
            for (i = 1; i < num; i++)
            {
                MyPoint tempP = a[i];
                a[i] = tempP.add(a[i - 1]);
            }
            return a;
        }
        private ArrayOfPoints createLine(int num)
        {
            //not conatin the first one (0,0); 
            //return a array with len of num-1
            ArrayOfPoints a = new ArrayOfPoints();
            for (int i = 0; i < num - 1; i++)
            {
                a.push(new MyPoint(i + 1, 0));
            }
            return a;
        }
        private ArrayOfPoints createSideLoop(int num)
        {
            //not contain the first one (0,0)
            //return a array with len of num-1
            ArrayOfPoints a = new ArrayOfPoints();
            switch (num)
            {
                case 2:
                    a.push(new MyPoint(0, -1));
                    break;
                case 3:
                    a.push(new MyPoint(Math.Sqrt(3) / 2, -0.5));
                    a.push(new MyPoint(0, -1));

                    break;
                case 4:
                    a.push(new MyPoint(Math.Sqrt(3) / 2, -0.5));
                    a.push(new MyPoint(Math.Sqrt(3) / 2, -1.5));
                    a.push(new MyPoint(0, -2));
                    break;
                default:
                    int numLen = 2 * (num - 1);
                    ArrayOfPoints loop = createLoop(numLen);
                    loop=loop.splice(0, 1);
                    double angle = Math.PI * (1 - (double)(numLen - 2) / (double)numLen) / 2.0;
                    for (int i = 0; i < loop.Length; i++)
                    {
                        loop[i] = rotateMyPoint(loop[i], angle);
                    }
                    arrayFill(loop, a, 0, num - 1);
                    a = arrayMulti(a, -1);
                    break;


            }
            return a;
        }
        //
        private MyPoint rotateMyPoint(MyPoint p, double a)
        {
            double cosa = Math.Cos(a);
            double sina = Math.Sin(a);
            return new MyPoint(p.X * cosa - p.Y * sina, p.X * sina + p.Y * cosa);
        }
        private MyPoint pointMulti(MyPoint p, double t)
        {
            return new MyPoint(p.X * t, p.Y * t);
        }
        //
        private ArrayOfPoints arrayMulti(ArrayOfPoints arr, double t)
        {
            return arrayMultiP(arr, new MyPoint(t, t));
        }
        private ArrayOfPoints arrayMultiP(ArrayOfPoints arr, MyPoint t)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                MyPoint p = arr[i];
                p.X *= t.X;
                p.Y *= t.Y;
                arr[i] = p;
            }
            return arr;
        }
        private ArrayOfPoints arrayAdd(ArrayOfPoints arr, MyPoint adden)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                MyPoint p = arr[i];
                arr[i] = p.add(adden);
            }
            return arr;
        }
        private void arrayFill(ArrayOfPoints from, ArrayOfPoints to, int start, int len = -1)
        {
            if (len == -1) len = from.Length;
            for (int i = 0; i < len; i++)
            {
                to[start + i] = from[i];
            }
        }
        //
        private RectangleF arrayGetRect(ArrayOfPoints arr)
        {
            double minX, maxX;
            double minY, maxY;
            minX = maxX = 0;
            minY = maxY = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                MyPoint p = arr[i];
                if (minX > p.X) minX = p.X;
                else if (maxX < p.X) maxX = p.X;
                if (minY > p.Y) minY = p.Y;
                else if (maxY < p.Y) maxY = p.Y;
            }

            return new RectangleF((float)minX, (float)minY, (float)(maxX - minX), (float)(maxY - minY));
        }
        private double arrayGetWidth(ArrayOfPoints arr)
        {
            //assume that the (0,0) is included in arr
            double minX, maxX;
            minX = maxX = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                MyPoint p = arr[i];
                if (minX > p.X) minX = p.X;
                else if (maxX < p.X) maxX = p.X;
            }
            return maxX - minX;
        }
        private double arrayGetHeight(ArrayOfPoints arr)
        {
            //assume that the (0,0) is included in arr
            double minY, maxY;
            minY = maxY = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                MyPoint p = arr[i];
                if (minY > p.Y) minY = p.Y;
                else if (maxY < p.Y) maxY = p.Y;
            }
            return maxY - minY;
        }
        //************end helpful math function**********
    }
    class ArrayOfPoints
    {
        private List<MyPoint> values;
        public ArrayOfPoints(int size = 0)
        {
            values = new List<MyPoint>(size);
        }
        public int push(MyPoint p)
        {
            values.Add(p);
            return values.Count;
        }


        public int Length
        {
            get
            {
                return values.Count;
            }

        }

        public MyPoint this[int index]
        {
            get
            {
                while (Length - 1 < index)
                {
                    values.Add(new MyPoint());

                }
                return values[index];
            }
            set
            {

                while (Length - 1 < index)
                {
                    values.Add(new MyPoint());

                }
                values[index] = value;


            }
        }
        public ArrayOfPoints splice(int startIndex, int deleteCount)
        {
            values.RemoveRange(startIndex, deleteCount);
            return this;
        }
        public ArrayOfPoints reverse()
        {
            values.Reverse();
            return this;
        }
        public override string ToString()
        {
            string str = "Array[";
            int i;
            for (i = 0; i < Length - 1; i++)
            {
                str += values[i].ToString() + ",";
            }
            str += values[i].ToString() + "]";
            return str;
        }

    }
    class MyPoint
    {
        private double _x, _y;
        public MyPoint(double x = 0.0f, double y = 0.0f)
        {
            _x = x;
            _y = y;
        }


        public double X
        {
            get
            {
                return _x;
            }
            set
            {
                _x = value;
            }
        }

        public double Y { get { return _y; } set { _y = value; } }
        public double Length { get { return Math.Sqrt(_x * _x + _y * _y); } }
        public MyPoint add(MyPoint p)
        {

            return new MyPoint(this.X + p.X, this.Y + p.Y);
        }
        public MyPoint sub(MyPoint p)
        {
            return new MyPoint(this.X - p.X, this.Y - p.Y);
        }

        public PointF toPointF()
        {
            return new PointF((float)_x, (float)_y);
        }
        public override string ToString()
        {
            return "Point(" + X + "," + Y + ")";
        }
    }
}
