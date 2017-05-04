
package pt.pkg2.java.swing;

import java.io.File;
import javax.swing.event.TreeModelListener;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

public class NewTreeModel implements TreeModel
{
        private File root;
        public NewTreeModel(File root)
        {
            this.root=root;
        }
        @Override
        public Object getRoot() {
            return root;
        }

        @Override
        public Object getChild(Object parent, int index) {
            
        File[] dzieci=((File)parent).listFiles();

        if(dzieci==null || index<0 || index>=dzieci.length) return null;
        
        File wynik;
        wynik = new FileExt(dzieci[index]);

        return wynik;
        }

        @Override
        public int getChildCount(Object parent) {
            String[] dzieci=((File)parent).list();
            if(dzieci==null) return 0;
            return dzieci.length;
        }

        @Override
        public boolean isLeaf(Object node) {
            if( ((File)node).isFile()) return true;
            else return false;
        }

        @Override
        public void valueForPathChanged(TreePath path, Object newValue) {
           // throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        @Override
        public int getIndexOfChild(Object parent, Object child) {
            
            if (parent==null || child==null)
                return -1;
            File[] dzieci=((File)parent).listFiles();
            
            for ( int i=0;i<dzieci.length; i++)
            {
                if(dzieci[i].equals((File)child))
                    return i;
            }
            return -1;
            
        }
        @Override
        public void addTreeModelListener(TreeModelListener l) {
//            throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }
        @Override
        public void removeTreeModelListener(TreeModelListener l) {
         //   throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }
   
}
