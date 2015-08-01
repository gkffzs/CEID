import java.awt.Graphics;
import java.awt.Font;
import java.awt.Color;

public class MyApplet extends java.applet.Applet {
    int fsize, x, y, r, g, b;
    String font;
    Font f;
    Color c;

    public void init() {
        x = 10;
        y = 20;
        font = "SansSerif";
        fsize = 24;
        f = new Font(font, Font.BOLD, fsize);
        c = Color.red;
    }

    public void start() {
        x += 10;
        y += 50;
        x %= 500;
        y %= 500;
        java.util.Random rand = new java.util.Random();
        r = rand.nextInt(255);
        g = rand.nextInt(255);
        b = rand.nextInt(255);
        c = new Color(r, g, b);
    }

    public void stop() {
        if (fsize > 10) fsize-=6; else fsize = 24;
        f = new Font(font, Font.BOLD, fsize);
    }

    public void paint(Graphics g) {
        g.setFont(f);
        g.setColor(c);
        g.drawString("niyon anomhmata mh monan oyin "+x+" "+y, x, y);
        g.drawString("ΝΙΨΟΝ ΑΝΟΜΗΜΑΤΑ ΜΗ ΜΟΝΑΝ ΟΨΙΝ "+x+" "+3*y, x, 3*y);
        g.drawLine(30, 30, 90, 200);
        g.fillOval(20, 40, 15, 35);
        g.fillRect(40, 10, 60, 30);
        Color c2=new Color(255-c.getRed(),255-c.getGreen(),255-c.getBlue());
        g.setColor(c2);
        g.fillArc(20, 40, 15, 35, 20, 100);
        g.fillRoundRect(40, 10, 60, 30, 30, 15);
        java.awt.Polygon poly = new java.awt.Polygon();
        poly.addPoint(30, 30);
        poly.addPoint(100, 196);
        poly.addPoint(93, 209);
        poly.addPoint(81, 203);
        poly.addPoint(30, 30);
        g.setColor(c);
        g.drawPolygon(poly);
        g.copyArea(0, 0, 120, 220, 50, 100);
        g.clearRect(0, 0, 120, 220);
        setBackground(c2);
    }
}