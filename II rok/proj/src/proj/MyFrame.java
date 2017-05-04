package proj;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;

public final class MyFrame extends JFrame {

    private final JSlider ElectronsAmountSlider;
    private final JSlider ElectronsSpeedSlider;
    private final JLabel ElectronsAmountLabel = new JLabel();
    private final JLabel ElectronsSpeedLabel = new JLabel();
    private final JLabel CurrentLabel = new JLabel();
    private final MyPanel ElectronsPanel;
    private final int DELAY = 5;

    @Override
    public void paint(Graphics g) {
        super.paint(g);

    }

    public void go() {
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                synchronized (MyPanel.getElectrons()) {

                    double temp = (ElectronsSpeedSlider.getValue()) / 4000.0;
                    double TimeInSec = (temp) / (DELAY / 1000.0) / 0.4;
                    String TimeStr = String.valueOf(TimeInSec);
                    if (TimeStr.length() > 3) {
                        TimeStr = TimeStr.substring(0, 3);
                    }
                    ElectronsSpeedLabel.setText(TimeStr);

                    ElectronsPanel.moveAll(1.0 / (ElectronsSpeedSlider.getValue() / 10.0));
                    for (int i = 0; i < 100; i++) {
                        ElectronsPanel.populate();
                    }
                    ElectronsAmountLabel.setText(String.valueOf(MyPanel.getElectrons().size()));
                    MyPanel.setBonusSpace(ElectronsAmountSlider.getValue());

                    try {
                        int Current = (int) (10 * MyPanel.getElectrons().size() / TimeInSec);
                        if (TimeInSec == 0) {
                            throw new Exception();
                        }
                        String CurrentStr = String.valueOf(Current / 10.0);
                        CurrentLabel.setText(CurrentStr);
                    } catch (Exception ex) {
                        CurrentLabel.setText("0.0");
                    }
                    repaint();
                }
            }
        };
        Timer timer = new Timer();
        timer.schedule(task, 0, DELAY);
    }

    public MyFrame() {
        super("Prąd elektryczny");
        this.setPreferredSize(new Dimension(500, 400));

        ElectronsPanel = new MyPanel(400, 100);
        ElectronsAmountSlider = new JSlider(0, 100);
        ElectronsAmountSlider.setPreferredSize(new Dimension(400, 50));
        ElectronsSpeedSlider = new JSlider(0, 30);
        ElectronsSpeedSlider.setPreferredSize(new Dimension(400, 50));

        JPanel ControlPanel;
        ControlPanel = new JPanel();
        ControlPanel.setPreferredSize(new Dimension(400, 200));
        ControlPanel.setMaximumSize(ControlPanel.getPreferredSize());

        ControlPanel.add(new JLabel("Ilość elektronów w [C]:"));
        ControlPanel.add(ElectronsAmountLabel);
        ControlPanel.add(ElectronsAmountSlider);

        ControlPanel.add(new JLabel("Czas przepływu ładunku w [s]:"));
        ControlPanel.add(ElectronsSpeedLabel);
        ControlPanel.add(ElectronsSpeedSlider);

        ControlPanel.add(new JLabel("Natężenie prądu elektrycznego w [N]:"));
        ControlPanel.add(CurrentLabel);

        Container pane = this.getContentPane();
        pane.setLayout(new BoxLayout(pane, BoxLayout.Y_AXIS));
        pane.add(ControlPanel);
        pane.add(ElectronsPanel);

        this.pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
        this.go();
    }
}
