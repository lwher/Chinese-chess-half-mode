#include "classes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

//red   0:帅 1:士 2:相 3:车 4:马 5:炮 6:兵
//black 7:将 8:士 9:象 10:车 11:马 12:炮 13:卒
//14: 空 15: 背面
// ty 0:没选中 1:选中
std::string ui_change(int id, int ty){
    std::string res = ":/picture/";
    switch(id){
        case 0:
            if(!ty) res += "RK.png";
            else res += "RKS.png";
            break;
        case 1:
            if(!ty) res += "RA.png";
            else res += "RAS.png";
            break;
        case 2:
            if(!ty) res += "RB.png";
            else res += "RBS.png";
            break;
        case 3:
            if(!ty) res += "RR.png";
            else res += "RRS.png";
            break;
        case 4:
            if(!ty) res += "RN.png";
            else res += "RNS.png";
            break;
        case 5:
            if(!ty) res += "RC.png";
            else res += "RCS.png";
            break;
        case 6:
            if(!ty) res += "RP.png";
            else res += "RPS.png";
            break;
        case 7:
            if(!ty) res += "BK.png";
            else res += "BKS.png";
            break;
        case 8:
            if(!ty) res += "BA.png";
            else res += "BAS.png";
            break;
        case 9:
            if(!ty) res += "BB.png";
            else res += "BBS.png";
            break;
        case 10:
            if(!ty) res += "BR.png";
            else res += "BRS.png";
            break;
        case 11:
            if(!ty) res += "BN.png";
            else res += "BNS.png";
            break;
        case 12:
            if(!ty) res += "BC.png";
            else res += "BCS.png";
            break;
        case 13:
            if(!ty) res += "BP.png";
            else res += "BPS.png";
            break;
        case 14:
            if(!ty) res += "blank.png";
            else res += "bS.png";
            break;
        case 15:
            res += "back.png";
            break;
    }
    return res;
}

void MainWindow::show_chess(int x, int y, int id, int ty){
    //QMessageBox::about(NULL, "提示", QString("%1 %2 %3 %4").arg(x).arg(y).arg(id).arg(ty));
    QPixmap pixmap(ui_change(id, ty).c_str());
    QIcon icon(pixmap);
    if(x == 1 && y == 1) ui->one_one->setIcon(icon); else
    if(x == 1 && y == 2) ui->one_two->setIcon(icon); else
    if(x == 1 && y == 3) ui->one_three->setIcon(icon); else
    if(x == 1 && y == 4) ui->one_four->setIcon(icon); else
    if(x == 1 && y == 5) ui->one_five->setIcon(icon); else
    if(x == 1 && y == 6) ui->one_six->setIcon(icon); else
    if(x == 1 && y == 7) ui->one_seven->setIcon(icon); else
    if(x == 1 && y == 8) ui->one_eight->setIcon(icon); else

    if(x == 2 && y == 1) ui->two_one->setIcon(icon); else
    if(x == 2 && y == 2) ui->two_two->setIcon(icon); else
    if(x == 2 && y == 3) ui->two_three->setIcon(icon); else
    if(x == 2 && y == 4) ui->two_four->setIcon(icon); else
    if(x == 2 && y == 5) ui->two_five->setIcon(icon); else
    if(x == 2 && y == 6) ui->two_six->setIcon(icon); else
    if(x == 2 && y == 7) ui->two_seven->setIcon(icon); else
    if(x == 2 && y == 8) ui->two_eight->setIcon(icon); else

    if(x == 3 && y == 1) ui->three_one->setIcon(icon); else
    if(x == 3 && y == 2) ui->three_two->setIcon(icon); else
    if(x == 3 && y == 3) ui->three_three->setIcon(icon); else
    if(x == 3 && y == 4) ui->three_four->setIcon(icon); else
    if(x == 3 && y == 5) ui->three_five->setIcon(icon); else
    if(x == 3 && y == 6) ui->three_six->setIcon(icon); else
    if(x == 3 && y == 7) ui->three_seven->setIcon(icon); else
    if(x == 3 && y == 8) ui->three_eight->setIcon(icon); else

    if(x == 4 && y == 1) ui->four_one->setIcon(icon); else
    if(x == 4 && y == 2) ui->four_two->setIcon(icon); else
    if(x == 4 && y == 3) ui->four_three->setIcon(icon); else
    if(x == 4 && y == 4) ui->four_four->setIcon(icon); else
    if(x == 4 && y == 5) ui->four_five->setIcon(icon); else
    if(x == 4 && y == 6) ui->four_six->setIcon(icon); else
    if(x == 4 && y == 7) ui->four_seven->setIcon(icon); else
    if(x == 4 && y == 8) ui->four_eight->setIcon(icon);
    inPro->processEvents();
}
