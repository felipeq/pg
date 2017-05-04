package proj;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;

public class Electron {

    private double x;
    private final double y;
    private final int width = 20;
    private final int height = 20;
    private final int StrokeSize = 5;

    private final Color StrokeColor = new Color(1, 1, 255);
    private final Color OvalColor = new Color(119, 119, 255);

    private final BasicStroke BorderStroke = new BasicStroke(StrokeSize);
    private final BasicStroke MinusStroke = new BasicStroke(2f);
    private final int MinusLength = 8;

    public Electron(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    void drawTo(Graphics2D g2d) {
        g2d.setColor(StrokeColor);
        g2d.setStroke(BorderStroke);
        g2d.drawOval((int) x, (int) y, width, height);
        g2d.setColor(OvalColor);
        int fixedWidth = width + StrokeSize / 2 - 1;
        int fixedHeight = height + StrokeSize / 2 - 1;
        g2d.fillOval((int) x, (int) y, fixedWidth, fixedHeight);
        g2d.setColor(Color.BLACK);
        g2d.setStroke(MinusStroke);
        g2d.drawLine((int) x + (fixedWidth - MinusLength) / 2, (int) y + fixedHeight / 2, (int) x + (fixedWidth + MinusLength) / 2, (int) y + fixedHeight / 2);
    }

    void moveX(double x) {
        this.x += x;
    }

}
