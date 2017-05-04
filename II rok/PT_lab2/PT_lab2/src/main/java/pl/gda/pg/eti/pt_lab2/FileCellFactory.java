/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.gda.pg.eti.pt_lab2;

import java.io.File;
import javafx.scene.control.TreeCell;
import javafx.scene.control.TreeView;

/**
 *
 * @author Filip
 */
public class FileCellFactory implements javafx.util.Callback<TreeView<File>, TreeCell<File>> {

    @Override
    public TreeCell<File> call(TreeView<File> p) {
        //System.out.println(p.getRoot().getValue().getName());
        FileCell temp = new FileCell();
        
        return temp;
    }

}
