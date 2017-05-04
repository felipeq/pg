package proj;

import java.awt.*;
import java.util.Random;
import java.util.concurrent.CopyOnWriteArrayList;
import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.border.Border;

public class MyPanel extends JPanel {

    private final int WINDOW_X;
    private final int WINDOW_Y;
    private static final CopyOnWriteArrayList<Electron> electrons = new CopyOnWriteArrayList<>();
    private static int bonusSpace = 15;

    public static CopyOnWriteArrayList<Electron> getElectrons() {
        return electrons;
    }

    public static void setBonusSpace(int bonusSpace) {
        if (bonusSpace <= 15) {
            MyPanel.bonusSpace = 100;
        } else {
            MyPanel.bonusSpace = 115 - bonusSpace;
        }
    }

    public MyPanel(int WINDOW_X, int WINDOW_Y) {
        this.WINDOW_X = WINDOW_X;
        this.WINDOW_Y = WINDOW_Y;
        this.setPreferredSize(new Dimension(WINDOW_X, WINDOW_Y));
        this.setMaximumSize(this.getPreferredSize());

        Border blackline = BorderFactory.createLineBorder(Color.black);
        this.setBorder(blackline);
        this.setBackground(Color.white);

    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        AntialiasMe(g2d);

        for (Electron e : electrons) {
            e.drawTo(g2d);
        }

    }

    protected void AntialiasMe(Graphics2D g) {
        g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                RenderingHints.VALUE_INTERPOLATION_BILINEAR);
    }

    public void moveAll(double x) {
        for (Electron e : electrons) {
            e.moveX(x);
            if (e.getX() - 2 > WINDOW_X) {
                electrons.remove(e);
            }
        }
    }

    public int Distance(int x1, int y1, Electron e) {
        int x2 = (int) e.getX();
        int y2 = (int) e.getY();
        int xd = x2 - x1;
        int yd = y2 - y1;
        return (int) Math.sqrt(xd * xd + yd * yd);
    }

    public void populate() {
        Random rand = new Random();
        int y = (int) (rand.nextDouble() * (WINDOW_Y - 25));
        int x = -25;
        for (Electron e : electrons) {
            if (Distance(x, y, e) <= bonusSpace) {
                return;
            }
        }

        electrons.add(new Electron(x, y));
    }

}
