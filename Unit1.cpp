//---------------------------------------------------------------------------

#include <vcl.h>
#include <Registry.hpp>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma link "CoolTrayIcon"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
       TStringList *s = new TStringList;
        TMemoryStream *fs = new TMemoryStream();
        s->Clear();
        s->Add("sLine=123");
        IdHTTP1->Request->Connection = "keep-alive";
        IdHTTP1->Request->ContentType = "application/x-www-form-urlencoded";
        IdHTTP1->Request->ContentLength = 9;
        IdHTTP1->HandleRedirects=true;
        try{
                IdHTTP1->Post( "http://www.yoursite.com/script_name.php",s,fs);

                // ## //
                fs->Seek(0, soFromBeginning);
                char buf[25];
                //ShowMessage(fs->Read(&buf, sizeof(fs)));
                // 1 - good
                // 2 - bad
                // ## //
                CoolTrayIcon1->ShowBalloonHint("rdp ip", "IP успешно отправлен", bitInfo, 10);
                Form1->Timer1->Enabled = true;
                Form1->Button1->Enabled = false;
        }
        catch(EIdHTTPProtocolException &se){
                switch(se.ErrorCode){
                                case 200:
                        break;
                                case 303:
                        break;
                                case 404:
                        break;
                                default:
                        break;
                }
       }
        catch(EIdSocketError &se){
                if(se.LastError == 11001 || se.LastError == 10054)
                        MessageBox(0, "Нет соединения с сетью Интернет.", 0, MB_OK + MB_ICONWARNING);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    TRegistry *reg = new TRegistry();
    reg->RootKey=HKEY_CURRENT_USER;
    reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
    
    if(reg->ValueExists("rdpip"))
        ShowMessage("Уже добавлено");
    else
        reg->WriteString("rdpip",Application->ExeName);

    reg->CloseKey();
    delete reg;
    reg = NULL;
    Button2->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
       TStringList *s = new TStringList;
        TMemoryStream *fs = new TMemoryStream();
        s->Clear();
        s->Add("sLine=123");
        IdHTTP1->Request->Connection = "keep-alive";
        IdHTTP1->Request->ContentType = "application/x-www-form-urlencoded";
        IdHTTP1->Request->ContentLength = 9;
        IdHTTP1->HandleRedirects=true;
        try{
                IdHTTP1->Post( "http://www.yoursite.com/script_name.php",s,fs);

                // ## //
                fs->Seek(0, soFromBeginning);
                char buf[25];
                //ShowMessage(fs->Read(&buf, sizeof(fs)));
                CoolTrayIcon1->ShowBalloonHint("rdp ip", "IP успешно отправлен", bitInfo, 10);
                // 1 - good
                // 2 - bad
                // ## //
        }
        catch(EIdHTTPProtocolException &se){
                switch(se.ErrorCode){
                                case 200:
                        break;
                                case 303:
                        break;
                                case 404:
                        break;
                                default:
                        break;
                }
       }
        catch(EIdSocketError &se){
                if(se.LastError == 11001 || se.LastError == 10054){
                        //MessageBox(0, "Net interneta", 0, MB_OK + MB_ICONWARNING);
                        CoolTrayIcon1->ShowBalloonHint("rdp ip", "Нет интернета. Повторый запрос через 5 минут.", bitInfo, 20);
                        Sleep(30000);  // Spim 5 minut
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    CoolTrayIcon1->IconVisible = true;
    
    TRegistry *reg = new TRegistry();
    reg->RootKey=HKEY_CURRENT_USER;
    reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);

    if(reg->ValueExists("rdpip")){
        Form1->Button2->Enabled = false;
        Form1->Button1->Enabled = false;

               TStringList *s = new TStringList;
        TMemoryStream *fs = new TMemoryStream();
        s->Clear();
        s->Add("sLine=123");
        IdHTTP1->Request->Connection = "keep-alive";
        IdHTTP1->Request->ContentType = "application/x-www-form-urlencoded";
        IdHTTP1->Request->ContentLength = 9;
        IdHTTP1->HandleRedirects=true;
        try{
                IdHTTP1->Post( "http://www.yoursite.com/script_name.php",s,fs);

                // ## //
                fs->Seek(0, soFromBeginning);
                char buf[25];
                //ShowMessage(fs->Read(&buf, sizeof(fs)));
                CoolTrayIcon1->ShowBalloonHint("rdp ip", "IP успешно отправлен", bitInfo, 10);
                // 1 - good
                // 2 - bad
                // ## //
        }
        catch(EIdHTTPProtocolException &se){
                switch(se.ErrorCode){
                                case 200:
                        break;
                                case 303:
                        break;
                                case 404:
                        break;
                                default:
                        break;
                }
       }
        catch(EIdSocketError &se){
                if(se.LastError == 11001 || se.LastError == 10054){
                        //MessageBox(0, "Net interneta", 0, MB_OK + MB_ICONWARNING);
                        CoolTrayIcon1->ShowBalloonHint("rdp ip", "Нет интернета. Повторый запрос через 5 минут.", bitInfo, 20);
                }
        }
        Form1->Timer2->Enabled = true;
        Form1->Timer1->Enabled = true;
    }

    reg->CloseKey();
    delete reg;
    reg = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
        CanClose = false;
        CoolTrayIcon1->ShowBalloonHint("rdp ip", "Свёрнуто в трей", bitInfo, 10);
        Form1->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
        CoolTrayIcon1->IconVisible = false;
        Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CoolTrayIcon1DblClick(TObject *Sender)
{
        Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        Form1->Hide();
        this->Enabled = false;
}
//---------------------------------------------------------------------------
