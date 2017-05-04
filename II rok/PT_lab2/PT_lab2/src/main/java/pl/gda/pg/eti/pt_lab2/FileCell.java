/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.gda.pg.eti.pt_lab2;

import java.io.File;
import javafx.scene.control.TreeCell;

/**
 *
 * @author Filip
 */
class FileCell extends TreeCell<File> {

    @Override
    protected void updateItem(File file, boolean empty) {
        super.updateItem(file, empty);

        if (file != null) {
            setText(file.getName());
        } else {
            setText(null);
        }
    }
    

}
