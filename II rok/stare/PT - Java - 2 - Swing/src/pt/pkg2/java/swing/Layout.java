package pt.pkg2.java.swing;

import java.io.File;
import java.io.IOException;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeSelectionModel;
/**
 *
 * @author filip
 */
public class Layout extends JFrame implements TreeSelectionListener 
{

    /**
     * Creates new form Layout
     */
    public Layout() {
        initComponents();
        OpenFolder.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        jTree1.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
        jTree1.addTreeSelectionListener(this);
    }
    

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        jTree1 = new javax.swing.JTree();
        Podglad = new javax.swing.JPanel();
        Informacje = new javax.swing.JLabel();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenuItem4 = new javax.swing.JMenuItem();
        jMenuItem2 = new javax.swing.JMenuItem();
        jMenu2 = new javax.swing.JMenu();
        jMenuItem3 = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Lab 2 - Filip Biedrzycki");

        jTree1.setName("Java Swing Lab 2 Filip Biedrzycki"); // NOI18N
        jScrollPane1.setViewportView(jTree1);

        Podglad.setBorder(javax.swing.BorderFactory.createEtchedBorder());

        javax.swing.GroupLayout PodgladLayout = new javax.swing.GroupLayout(Podglad);
        Podglad.setLayout(PodgladLayout);
        PodgladLayout.setHorizontalGroup(
            PodgladLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        PodgladLayout.setVerticalGroup(
            PodgladLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 350, Short.MAX_VALUE)
        );

        Informacje.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        Informacje.setName("info"); // NOI18N

        jMenu1.setText("File");

        jMenuItem1.setText("Open Folder");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem1);

        jMenuItem4.setText("Create Folder/File");
        jMenuItem4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem4ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem4);

        jMenuItem2.setText("Close");
        jMenuItem2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem2ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem2);

        jMenuBar1.add(jMenu1);

        jMenu2.setText("About");

        jMenuItem3.setText("About");
        jMenuItem3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem3ActionPerformed(evt);
            }
        });
        jMenu2.add(jMenuItem3);

        jMenuBar1.add(jMenu2);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 250, Short.MAX_VALUE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(Podglad, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(Informacje, javax.swing.GroupLayout.DEFAULT_SIZE, 408, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Podglad, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(Informacje, javax.swing.GroupLayout.PREFERRED_SIZE, 76, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 436, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        if (OpenFolder.showOpenDialog(this)==JFileChooser.APPROVE_OPTION)
        {
            File wybrany=new File(OpenFolder.getSelectedFile().getAbsolutePath());
            TreeModel model=new NewTreeModel(wybrany);
            jTree1.setModel(model);
        }
    }//GEN-LAST:event_jMenuItem1ActionPerformed

    private void jMenuItem3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem3ActionPerformed
        JOptionPane.showMessageDialog(this,"Java - Swing \n Filip Biedrzycki\n Grupa 5, 2013","About",JOptionPane.INFORMATION_MESSAGE);
    }//GEN-LAST:event_jMenuItem3ActionPerformed

    private void jMenuItem2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem2ActionPerformed
        System.exit(0);
    }//GEN-LAST:event_jMenuItem2ActionPerformed

    private void jMenuItem4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem4ActionPerformed
    File rodzic = (File)jTree1.getLastSelectedPathComponent();
    if (rodzic==null)
    {
        JOptionPane.showMessageDialog(this, "Wybierz katalog, w którym chcesz utworzyć nowy element!");
        return;
    }
    if (rodzic.isFile())
    {
        JOptionPane.showMessageDialog(this, "Wybrano plik, wybierz katalog!");
        return;
    }
    CreateFile.setVisible(true);
       
    }//GEN-LAST:event_jMenuItem4ActionPerformed
        public void CreateFile(String nazwa, int typ) // typ==0 < katalog, 1 < plik
    {
        CreateFile.setVisible(false);
        File rodzic = (File)jTree1.getLastSelectedPathComponent();
        File nowy = new File(rodzic.getPath() + "/" + nazwa);
        if (typ==0)
            if(!nowy.mkdir())
            {
                JOptionPane.showMessageDialog(this,"Błąd tworzenia folderu!","Error",JOptionPane.WARNING_MESSAGE);
                return;
            }
        if (typ==1)
            try
            {
                if(!nowy.createNewFile())
                {
                    JOptionPane.showMessageDialog(this,"Can't create a file.","Error",JOptionPane.WARNING_MESSAGE);
                    return;
                }
            }
            catch(IOException ex)
            {
                JOptionPane.showMessageDialog(this,"Can't create a file.","Error",JOptionPane.WARNING_MESSAGE);
                return;
            }
        TreeModel model;
        
            
        if (typ==1)
        {
            
            model=new NewTreeModel(nowy.getParentFile().getParentFile());
            Informacje.setText(nowy.getName());
        }
        else
            model=new NewTreeModel(nowy.getParentFile());
        jTree1.setModel(model);
            
    }
    @Override
          public void valueChanged(TreeSelectionEvent e) 
    {
        FileExt plik;
        if(jTree1.getLastSelectedPathComponent() instanceof FileExt)
        {
            plik = (FileExt)jTree1.getLastSelectedPathComponent();
        }
        else
        {
            Informacje.setText("");
            return;
        }
        if(plik.isDirectory()) 
            Informacje.setText("");
        else 
            Informacje.setText(plik.fileInfo());
    }
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Layout.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Layout.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Layout.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Layout.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Layout().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel Informacje;
    private javax.swing.JPanel Podglad;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JMenuItem jMenuItem2;
    private javax.swing.JMenuItem jMenuItem3;
    private javax.swing.JMenuItem jMenuItem4;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTree jTree1;
    // End of variables declaration//GEN-END:variables
    private JFileChooser OpenFolder = new JFileChooser();
    private FileCreator CreateFile=new FileCreator(this);
}

