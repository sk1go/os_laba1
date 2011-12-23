/////////////////////////////////////////////////////////////////////////////
//#include <stdio.h>
//#include <stdlib.h>
//
//#define Error( Str )        FatalError( Str )
//#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
/////////////////////////////////////////////////////////////////////////////
unit sint_analiz;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    GroupBox1: TGroupBox;
    procedure Button1Click(Sender: TObject);
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure FormActivate(Sender: TObject);


  private
    { Private declarations }
  public
    { Public declarations }
  end;
type str2 = string[2];
const
  Rims : array[1..14] of str2 = ('M','CM','D','CD','C','XC','L','XL','X','IX','V','IV','I',' '); 
  Arab : array[1..14] of integer = (1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1, 0);
  simple: array[1..13] of string = ('null','eins','zwei','drei','vier','funf','sechs','sieben','acht','neun','zehn','elf','zwolf');
  hard:   array[1..4]  of string = ('ein','zwan','sech','sieb');
  dec:    array[1..8]  of string = ('zwanzig','dreizig','vierzig','funfzig','sechzig','siebzig','achtzig','neunzig');
  und='und';
  zig='zig';
  zehn='zehn';
var
  Form1: TForm1;



implementation

{$R *.dfm}
function DestroyAllWhiteSpace(S : String) : String;
//удаляет все лишние пробелы из строки
var
i : Integer;
begin
 for I:=1 to Length(S) do {делаем до длины строки}
  begin
  //if (S[I]=' ')and(S[I+1]=' ')or(S[I]=' ')and((I=1)or(I=Length(S)))then {проверяем на пробелы и 1-й и последний символы }
    if (S[I]=' ') then
    begin {да, есть лишние}
     Delete (S, I, 1); {удаляем их}
     S := DestroyAllWhiteSpace (S); {и снова проверяем}
    end; {рекурсия происходит до тех пор, пока строка не примет нормальный вид}
   end;
 Result := S; {результат}
end;

  function Arab2Rim(N : integer) : string; 
  var S : string; 
      I : integer; 
  begin 
    S := ''; I:=1;
    while N > 0 do begin 
      while Arab[I]<=N do begin 
        S := S + Rims[I]; 
        N := N - Arab[I]
      end; 
      I:=I+1 
    end;
    Arab2Rim := S
  end;

procedure WToD(first:string;hund:boolean;second:string;dec:string;zehn:boolean);
var sum:integer;
begin
sum:=0;
if hund then begin
             if first='ein'then sum:=sum+100;
             if first='zwan'then sum:=sum+200;
             if first='drei'then sum:=sum+300;
             if first='vier'then sum:=sum+400;
             if first='funf'then sum:=sum+500;
             if first='sech'then sum:=sum+600;
             if first='sieb'then sum:=sum+700;
             if first='acht'then sum:=sum+800;
             if first='neun'then sum:=sum+900;
             end;


            if dec='zwanzig'then sum:=sum+20;
            if dec='dreizig'then sum:=sum+30;
            if dec='vierzig'then sum:=sum+40;
            if dec='funfzig'then sum:=sum+50;
            if dec='sechzig'then sum:=sum+60;
            if dec='siebzig'then sum:=sum+70;
            if dec='achtzig'then sum:=sum+80;
            if dec='neunzig'then sum:=sum+90;



            if second='null'then sum:=sum+0;
            if second='eins'then sum:=sum+1;
            if second='ein'then sum:=sum+1;
            if second='zwei'then sum:=sum+2;
            if second='zwan'then sum:=sum+2;
            if second='drei'then if zehn then sum:=sum+13 else sum:=sum+3;
            if second='vier'then if zehn then sum:=sum+14 else sum:=sum+4;
            if second='funf'then if zehn then sum:=sum+15 else sum:=sum+5;
            if second='sechs'then sum:=sum+6;
            if second='sech'then if zehn then sum:=sum+16 else sum:=sum+6;
            if second='sieben'then sum:=sum+7;
            if second='sieb'then if zehn then sum:=sum+17 else sum:=sum+7;
            if second='acht'then if zehn then sum:=sum+18 else sum:=sum+8;
            if second='neun'then if zehn then sum:=sum+19 else sum:=sum+9;
            if second='zehn'then sum:=sum+10;
            if second='elf'then sum:=sum+11;
            if second='zwolf'then sum:=sum+12;

form1.label1.caption:=inttostr(sum);
form1.label2.caption:=Arab2Rim(sum);
end;

procedure TForm1.Button1Click(Sender: TObject);
var str,str_hund,s:string;
i,j,k,l,g,z,zs,zh,zd,zu,ku:integer;
flag1,flag2,flag3,flag4,flag5,flags,flagh,flagd:boolean;
 begin
str:=LowerCase(DestroyAllWhiteSpace(edit1.Text));
flag1:=false;
flag2:=false;
flag4:=false;
flag3:=true;
flag5:=false;
flags:=true;
flagh:=true;
flagd:=true;
label1.Caption:='';
label2.Caption:='';

for i:=1 to 13 do
if pos(simple[i],str)=1 then begin flag1:=true;break; end;

if flag1 then if length(str)=length(simple[i]) then WToD('',false,simple[i],'',false)
              else if (simple[i]='null')or(simple[i]='eins')or(simple[i]='zwei')or(simple[i]='sechs')or(simple[i]='sieben')or(simple[i]='zehn')or(simple[i]='elf')or(simple[i]='zwolf') then begin
                                                                                                                                                                                             s:=copy(str,pos(simple[i],str)+length(simple[i]),length(str)-length(simple[i]));
                                                                                                                                                                                             showmessage('После '+simple[i]+' (1-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                             end
                   else if pos('hundert',str)= length(simple[i])+1 then if length(str)=(length(simple[i])+7) then WToD(simple[i],true,'','',false) else begin
                                                                                                                                                        for j:=1 to 13 do begin
                                                                                                                                                                          str_hund:=copy(str,length(simple[i])+7+1,length(str));
                                                                                                                                                                          if pos(simple[j],str_hund)=1 then begin
                                                                                                                                                                                                            flag2:=true;
                                                                                                                                                                                                            break;
                                                                                                                                                                                                            end;
                                                                                                                                                                          end;
                                                                                                                                                        if flag2 then if length(str_hund)=length(simple[j]) then WToD(simple[i],true,simple[j],'',false)
                                                                                                                                                                      else if (simple[j]='null')or(simple[j]='eins')or(simple[j]='zwei')or(simple[j]='sechs')or(simple[j]='sieben')or(simple[j]='zehn')or(simple[j]='elf')or(simple[j]='zwolf') then begin
                                                                                                                                                                                                                                                                                                                                                     if simple[j]='eins' then begin
                                                                                                                                                                                                                                                                                                                                                                              if pos('siebzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                                                                                                s:=copy(str_hund,pos('ein',str_hund)+3,pos('siebzig',str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                                                                                                                                                                                                                                                showmessage('После ein (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                                                                                                end
                                                                                                                                                                                                                                                                                                                                                                              else if pos('sechzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                                                                                                     s:=copy(str_hund,pos('ein',str_hund)+3,pos('sechzig',str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                                                                                                                                                                                                                                                     showmessage('После ein (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                                                                                                     end
                                                                                                                                                                                                                                                                                                                                                                                   else begin
                                                                                                                                                                                                                                                                                                                                                                                        s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)-length(simple[j]));
                                                                                                                                                                                                                                                                                                                                                                                        showmessage('После '+simple[j]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                                                                                                        end
                                                                                                                                                                                                                                                                                                                                                                              end
                                                                                                                                                                                                                                                                                                                                                     else if simple[j]='sechs' then begin
                                                                                                                                                                                                                                                                                                                                                                                    if pos('siebzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                                                                                                      s:=copy(str_hund,pos('sech',str_hund)+4,pos('siebzig',str_hund)-(pos('sech',str_hund)+4));
                                                                                                                                                                                                                                                                                                                                                                                                                      showmessage('После sech (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                                                                                                      end
                                                                                                                                                                                                                                                                                                                                                                                    else if pos('sechzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                                                                                                           s:=copy(str_hund,pos('sech',str_hund)+4,pos('sechzig',str_hund)-(pos('sech',str_hund)+4));
                                                                                                                                                                                                                                                                                                                                                                                                                           showmessage('После sech (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                                                                                                           end
                                                                                                                                                                                                                                                                                                                                                                                         else begin
                                                                                                                                                                                                                                                                                                                                                                                              s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)-length(simple[j]));
                                                                                                                                                                                                                                                                                                                                                                                              showmessage('После '+simple[j]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                                                                                                              end
                                                                                                                                                                                                                                                                                                                                                                                    end
                                                                                                                                                                                                                                                                                                                                                          else begin
                                                                                                                                                                                                                                                                                                                                                               s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)-length(simple[j]));
                                                                                                                                                                                                                                                                                                                                                               showmessage('После '+simple[j]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                                                                               end
                                                                                                                                                                                                                                                                                                                                                     end
                                                                                                                                                                           else if pos(zig,str_hund)=length(simple[j])+1 then if length(str_hund)=(length(simple[j])+3) then WToD(simple[i],true,'',simple[j]+'zig',false) else begin
                                                                                                                                                                                                                                                                                                                                s:=copy(str_hund,pos(zig,str_hund)+3,length(str_hund));
                                                                                                                                                                                                                                                                                                                                showmessage('После '+simple[j]+zig+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                                                end
                                                                                                                                                                                else if pos(zehn,str_hund)=length(simple[j])+1 then if length(str_hund)=(length(simple[j])+4) then WToD(simple[i],true,simple[j],'',true) else begin
                                                                                                                                                                                                                                                                                                                               s:=copy(str_hund,pos(zehn,str_hund)+4,length(str_hund));
                                                                                                                                                                                                                                                                                                                               showmessage('После '+simple[j]+zehn+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                                               end
                                                                                                                                                                                     else if pos(und,str_hund)=length(simple[j])+1 then begin
                                                                                                                                                                                                                                        for k:=1 to 8 do
                                                                                                                                                                                                                                        if pos(dec[k],str_hund)=(length(simple[j])+3+1) then if length(str_hund)=(length(simple[j])+10) then begin flag3:=false; WToD(simple[i],true,simple[j],dec[k],false);end
                                                                                                                                                                                                                                                                                             else begin
                                                                                                                                                                                                                                                                                                  flag3:=false;
                                                                                                                                                                                                                                                                                                  s:=copy(str_hund,pos(dec[k],str_hund)+length(dec[k]),length(str_hund));
                                                                                                                                                                                                                                                                                                  showmessage('После '+dec[k]+' (5-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                                                  end;
                                                                                                                                                                                                                                        if flag3 then begin
                                                                                                                                                                                                                                                      for k:=1 to 8 do
                                                                                                                                                                                                                                                      if pos(dec[k],str_hund)>length(simple[j])+3 then begin
                                                                                                                                                                                                                                                                                                       flag3:=false;
                                                                                                                                                                                                                                                                                                       s:=copy(str_hund,pos(und,str_hund)+3,pos(dec[k],str_hund)-(pos(und,str_hund)+3));
                                                                                                                                                                                                                                                                                                       showmessage('После und (4-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                                                       end;
                                                                                                                                                                                                                                                      if flag3 then begin s:=copy(str_hund,pos(und,str_hund)+3,length(str_hund)); showmessage('После und (4-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                                                                                                                                                                      end
                                                                                                                                                                                                                                        end
                                                                                                                                                                                          else begin
                                                                                                                                                                                               for k:=1 to 8 do
                                                                                                                                                                                               if pos(und,str_hund)=0 then if pos(dec[k],str_hund)>length(simple[j]) then begin
                                                                                                                                                                                                                                                                          flag3:=false;
                                                                                                                                                                                                                                                                          s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),pos(dec[k],str_hund)-(pos(simple[j],str_hund)+length(simple[j])));
                                                                                                                                                                                                                                                                          showmessage('После '+simple[j]+' (3-е слово) '+'должно быть und'+#13+'добавьте/исправьте: '+s);
                                                                                                                                                                                                                                                                          end
                                                                                                                                                                                                                           else
                                                                                                                                                                                               else
                                                                                                                                                                                               if pos(dec[k],str_hund)>length(simple[j]) then begin
                                                                                                                                                                                                                                              flag3:=false;
                                                                                                                                                                                                                                              s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),pos(und,str_hund)-(pos(simple[j],str_hund)+length(simple[j])));
                                                                                                                                                                                                                                              showmessage('После '+simple[j]+' (3-е слово) '+'должно быть und'+#13+'удалите: '+s);
                                                                                                                                                                                                                                              end;
                                                                                                                                                                                               if flag3 then begin s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)); showmessage('После '+simple[j]+' (3-е слово) бессмыслица'+#13+'исправьте/удалите: '+s)end
                                                                                                                                                                                               end
                                                                                                                                                        else begin
                                                                                                                                                             for k:=1 to 4 do if pos(hard[k],str_hund)=1 then begin
                                                                                                                                                                                                              flag4:=true;
                                                                                                                                                                                                              break;
                                                                                                                                                                                                              end;
                                                                                                                                                             if flag4 then if hard[k]='ein' then if length(str_hund)=3 then showmessage('После hundert (2-еслово) не должно быть только ein'+#13'добавьте: und + десятки')
                                                                                                                                                                                                 else if pos(und,str_hund)=(3+1) then begin
                                                                                                                                                                                                                                      for l:=1 to 8 do
                                                                                                                                                                                                                                      if pos(dec[l],str_hund)=(3+3+1) then if length(str_hund)=(3+3+7) then begin WToD(simple[i],true,hard[k],dec[l],false); break; end
                                                                                                                                                                                                                                                                           else begin
                                                                                                                                                                                                                                                                                s:=copy(str_hund,pos(dec[l],str_hund)+length(dec[l]),length(str_hund));
                                                                                                                                                                                                                                                                                showmessage('После '+dec[l]+' (5-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                                break;
                                                                                                                                                                                                                                                                                end
                                                                                                                                                                                                                                      else if l=8 then begin
                                                                                                                                                                                                                                                       for z:=1 to 8 do
                                                                                                                                                                                                                                                       if pos(dec[z],str_hund)>3+3 then begin
                                                                                                                                                                                                                                                                                        flag3:=false;
                                                                                                                                                                                                                                                                                        s:=copy(str_hund,pos(und,str_hund)+3,pos(dec[z],str_hund)-(pos(und,str_hund)+3));
                                                                                                                                                                                                                                                                                        showmessage('После und  (4-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                                        end;
                                                                                                                                                                                                                                                       if flag3 then begin s:=copy(str_hund,pos(und,str_hund)+3,length(str_hund)); showmessage('После und (4-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                                                                                                                                                                       end;
                                                                                                                                                                                                                                      end
                                                                                                                                                                                                      else begin
                                                                                                                                                                                                           for k:=1 to 8 do
                                                                                                                                                                                                           if pos(und,str_hund)=0 then if pos(dec[k],str_hund)>3 then begin
                                                                                                                                                                                                                                                                      flag3:=false;s:=copy(str_hund,pos('ein',str_hund)+3,pos(dec[k],str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                                                                                                      showmessage('После ein (3-е слово) '+'должно быть und'+#13+'добавьте/исправьте: '+s);
                                                                                                                                                                                                                                                                      end
                                                                                                                                                                                                                                       else
                                                                                                                                                                                                           else if pos(dec[k],str_hund)>3 then begin
                                                                                                                                                                                                                                               flag3:=false;
                                                                                                                                                                                                                                               s:=copy(str_hund,pos('ein',str_hund)+3,pos(und,str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                                                                               showmessage('После ein'+' (3-е слово) '+'должно быть und'+#13+'удалите: '+s);
                                                                                                                                                                                                                                               end;
                                                                                                                                                                                                           if flag3 then begin s:=copy(str_hund,pos('ein',str_hund)+3,length(str_hund)); showmessage('После ein (3-е слово) бессмыслица'+#13+'исправьте/удалите: '+s)end;
                                                                                                                                                                                                           end
                                                                                                                                                                           else  if length(str_hund)=length(hard[k]) then showmessage('После '+str_hund+' (3-е слово) не хватает: '+#13+'und + десятки, zig или zehn')
                                                                                                                                                                                 else if pos(und,str_hund)=(4+1) then if length(str_hund)=(4+3) then showmessage('После '+und+' (4-е слово)'+#13+'не хватает: десятков')
                                                                                                                                                                                                                      else begin
                                                                                                                                                                                                                           for l:=1 to 8 do
                                                                                                                                                                                                                           if pos(dec[l],str_hund)=(4+3+1) then if length(str_hund)=(4+3+7) then begin WToD(simple[i],true,hard[k],dec[l],false);break; end
                                                                                                                                                                                                                                                                else begin
                                                                                                                                                                                                                                                                     s:=copy(str_hund,pos(dec[l],str_hund)+length(dec[l]),length(str_hund));
                                                                                                                                                                                                                                                                     showmessage('После '+dec[l]+' (5-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                     break;
                                                                                                                                                                                                                                                                     end
                                                                                                                                                                                                                           else if l=8 then begin
                                                                                                                                                                                                                                            for z:=1 to 8 do
                                                                                                                                                                                                                                            if pos(dec[z],str_hund)>length(hard[k])+3 then begin
                                                                                                                                                                                                                                                                                           flag3:=false;
                                                                                                                                                                                                                                                                                           s:=copy(str_hund,pos(und,str_hund)+3,pos(dec[z],str_hund)-(pos(und,str_hund)+3));
                                                                                                                                                                                                                                                                                           showmessage('После und  (4-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                                           end;
                                                                                                                                                                                                                                            if flag3 then begin s:=copy(str_hund,pos(und,str_hund)+3,length(str_hund)); showmessage('После und (4-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                                                                                                                                                            end;
                                                                                                                                                                                                                           end
                                                                                                                                                                                      else if pos(zig,str_hund)=(4+1) then if length(str_hund)=(4+3)then WToD(simple[i],true,'',hard[k]+'zig',false)
                                                                                                                                                                                                                           else begin s:=copy(str_hund,pos(zig,str_hund)+3,length(str_hund)); showmessage('После '+hard[k]+zig+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s) end
                                                                                                                                                                                           else if pos(zehn,str_hund)=(4+1) then if length(str_hund)=(4+4)then if hard[k]<>'zwan' then WToD(simple[i],true,hard[k],'',true)
                                                                                                                                                                                                                                                               else showmessage('После zwan (3-е слово) нельзя zehn')
                                                                                                                                                                                                                                 else begin s:=copy(str_hund,pos(zehn,str_hund)+4,length(str_hund)); showmessage('После '+hard[k]+zehn+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s) end
                                                                                                                                                             else begin                                                                                                                
                                                                                                                                                                  for z:=1 to 8 do
                                                                                                                                                                  if pos(und,str_hund)=0 then if pos(dec[z],str_hund)>3 then begin
                                                                                                                                                                                                                             flag3:=false;
                                                                                                                                                                                                                             s:=copy(str_hund,pos(hard[k],str_hund)+length(hard[k]),pos(dec[z],str_hund)-(pos(hard[k],str_hund)+length(hard[k])));
                                                                                                                                                                                                                             showmessage('После '+hard[k]+'(3-е слово) '+'должно быть und'+#13+'добавьте/исправьте: '+s);
                                                                                                                                                                                                                             end
                                                                                                                                                                                              else
                                                                                                                                                                  else if pos(dec[z],str_hund)>3 then begin
                                                                                                                                                                                                      flag3:=false;
                                                                                                                                                                                                      s:=copy(str_hund,pos(hard[k],str_hund)+length(hard[k]),pos(und,str_hund)-(pos(hard[k],str_hund)+length(hard[k])));
                                                                                                                                                                                                      showmessage('После '+hard[k]+'(3-е слово) '+'должно быть und'+#13+'удалите: '+s);
                                                                                                                                                                                                      end;
                                                                                                                                                                  if flag3 then begin s:=copy(str_hund,pos(hard[k],str_hund)+length(hard[k]),length(str_hund)); showmessage('После '+hard[k]+' (3-е слово) бессмыслица'+#13+'исправьте/удалите: '+s)end;
                                                                                                                                                                  end
                                                                        else begin
                                                                             str_hund:=copy(str,pos('hundert',str)+7,length(str));
                                                                             for zs:=1 to 13 do
                                                                             if pos(simple[zs],str_hund)<>0 then begin flags:=false; break;end;
                                                                             for zh:=1 to 4 do
                                                                             if pos(hard[zh],str)>pos('hundert',str)then begin flagh:=false;break;end;

                                                                             if flags and flagh then showmessage('После hundert (2-е слово) ничего не должно быть'+#13+'удалите: '+str_hund);
                                                                             if (not flags )and flagh  then begin
                                                                                                            for zd:=1 to 8 do if pos(dec[zd],str_hund)>0 then begin flagd:=false;break; end;
                                                                                                            if flagd then begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                            else if pos(dec[zd],str_hund)>pos(simple[zs],str_hund)then begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                 else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                            end;
                                                                             if flags and (not flagh)  then begin
                                                                                                            for zd:=1 to 8 do if pos(dec[zd],str_hund)>0 then begin flagd:=false;break; end;
                                                                                                            if flagd then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                            else if pos(dec[zd],str_hund)>pos(hard[zh],str_hund) then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                 else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                            end;
                                                                             if (not flags) and (not flagh) then begin
                                                                                                                 for zd:=1 to 8 do if pos(dec[zd],str_hund)>0 then begin flagd:=false;break; end;
                                                                                                                 if flagd then if pos(simple[zs],str_hund)>pos(hard[zh],str_hund)then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                               else begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                 else if pos(simple[zs],str_hund)>pos(hard[zh],str_hund)then begin
                                                                                                                                                                             if pos(dec[zd],str_hund)>pos(hard[zh],str_hund) then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                                                                             else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                                                                                             end
                                                                                                                      else begin
                                                                                                                           if pos(dec[zd],str_hund)>pos(simple[zs],str_hund)then begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                           else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                                           end;
                                                                                                                 end;
                                                                             end
                                                                                                                                                             end
                                                                                                                                                        end
                        else if pos(zig,str)= length(simple[i])+1 then if length(str)=(length(simple[i])+3)then WToD('',false,'',simple[i]+'zig',false)
                                                                       else begin s:=copy(str,pos(zig,str)+3,length(str)); showmessage('После '+simple[i]+zig+' (1-е слово) ничего не должно быть'+#13+'удалите: '+s) end
                             else if pos(zehn,str)= length(simple[i])+1 then if length(str)=(length(simple[i])+4)then WToD('',false,simple[i],'',true)
                                                                             else begin s:=copy(str,pos(zehn,str)+4,length(str)); showmessage('После '+simple[i]+zehn+' (1-е слово) ничего не должно быть'+#13+'удалите: '+s) end
                                  else if pos(und,str)=(length(simple[i])+1) then if length(str)=(length(simple[i])+3) then showmessage('После und (2-е слово) должны быть десятки')
                                                                                  else begin             
                                                                                       for l:=1 to 8 do
                                                                                       if pos(dec[l],str)=(length(simple[i])+3+1) then if length(str)=(length(simple[i])+3+7) then
                                                                                                                                                                              begin
                                                                                                                                                                              WToD('',false,simple[i],dec[l],false) ;
                                                                                                                                                                              break;
                                                                                                                                                                              end
                                                                                                                                       else begin
                                                                                                                                            s:=copy(str,pos(dec[l],str)+length(dec[l]),length(str));
                                                                                                                                            showmessage('После '+dec[l]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                            break;
                                                                                                                                            end
                                                                                       else if l=8 then begin
                                                                                                        for z:=1 to 8 do
                                                                                                        if pos(dec[z],str)>length(simple[i])+3 then begin
                                                                                                                                                    flag3:=false;
                                                                                                                                                    s:=copy(str,pos(und,str)+3,pos(dec[z],str)-(pos(und,str)+3));
                                                                                                                                                    showmessage('После und  (2-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                    end ;
                                                                                                        if flag3 then begin s:=copy(str,pos(und,str)+3,length(str)); showmessage('После und (2-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                        end;
                                                                                       end
                                       else begin
                                            if length(str)>length(simple[i])then begin
                                                                                 for zu:=1 to 8 do
                                                                                 if pos(dec[zu],str)>length(simple[i]) then begin
                                                                                                                           flag3:=false;
                                                                                                                           if pos(und,str)=0 then begin
                                                                                                                                                  s:=copy(str,pos(simple[i],str)+length(simple[i]),pos(dec[zu],str)-(pos(simple[i],str)+length(simple[i])));
                                                                                                                                                  showmessage('После '+simple[i]+' (1-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                                  end
                                                                                                                           else if pos(und,str)<pos(dec[zu],str) then begin
                                                                                                                                                                      s:=copy(str,pos(simple[i],str)+length(simple[i]),pos(und,str)-(pos(simple[i],str)+length(simple[i])));
                                                                                                                                                                      showmessage('После '+simple[i]+' (1-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                                                      end
                                                                                                                                else begin
                                                                                                                                     s:=copy(str,pos(simple[i],str)+length(simple[i]),pos(dec[zu],str)-(pos(simple[i],str)+length(simple[i])));
                                                                                                                                     showmessage('После '+simple[i]+' (1-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                     end;
                                                                                                                           end ;
                                                                                 if flag3 and(pos('hundert',str)=0) then begin s:=copy(str,pos(simple[i],str)+length(simple[i]),length(str)); showmessage('После '+simple[i]+' (1-е слово) бессмыслица'+#13+'исправьте/удалите: '+s);end
                                                                                 else begin s:=copy(str,pos(simple[i],str)+length(simple[i]),pos('hundert',str)-(pos(simple[i],str)+length(simple[i]))); showmessage('После '+simple[i]+' (1-е слово) может быть hundert'+#13+'удалите: '+s); end;
                                                                                 end
                                            end;
{=========================================================================================================================hard here=======================================================================================================}
flag4:=false;
for i:=1 to 4 do
if pos(hard[i],str)=1 then begin
                           flag4:=true;
                           break;
                           end;
if flag4=true then if length(str)=length(hard[i]) then showmessage('После '+hard[i]+' (1-е слово) не хватает und+десятки/zehn/zig/hundert')
                   else if pos('hundert',str)=(length(hard[i])+1) then if length(str)=length(hard[i])+7 then WToD(hard[i],true,'','',false)
                                                                       else begin
                                                                            for j:=1 to 13 do if pos(simple[j],str)=length(hard[i])+7+1 then begin
                                                                                                                                             flag1:=true;
                                                                                                                                             str_hund:=copy(str,length(hard[i])+7+1,length(str));
                                                                                                                                             break;
                                                                                                                                             end;
                                                                            if flag1 then if length(str)=length(hard[i])+7+length(simple[j]) then WToD(hard[i],true,simple[j],'',false)
                                                                                          else if (simple[j]='null')or(simple[j]='eins')or(simple[j]='zwei')or(simple[j]='sechs')or(simple[j]='sieben')or(simple[j]='zehn')or(simple[j]='elf')or(simple[j]='zwolf') then begin
                                                                                                                                                                                                                                                                         if simple[j]='eins' then begin
                                                                                                                                                                                                                                                                                                  if pos('siebzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                    s:=copy(str_hund,pos('ein',str_hund)+3,pos('siebzig',str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                                                                                                                                                                    showmessage('После ein (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                    end
                                                                                                                                                                                                                                                                                                  else if pos('sechzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                         s:=copy(str_hund,pos('ein',str_hund)+3,pos('sechzig',str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                                                                                                                                                                         showmessage('После ein (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                         end
                                                                                                                                                                                                                                                                                                       else begin
                                                                                                                                                                                                                                                                                                            s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)-length(simple[j]));
                                                                                                                                                                                                                                                                                                            showmessage('После '+simple[j]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                            end
                                                                                                                                                                                                                                                                                                  end
                                                                                                                                                                                                                                                                         else if simple[j]='sechs' then begin
                                                                                                                                                                                                                                                                                                        if pos('siebzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                          s:=copy(str_hund,pos('sech',str_hund)+4,pos('siebzig',str_hund)-(pos('sech',str_hund)+4));
                                                                                                                                                                                                                                                                                                                                          showmessage('После sech (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                          end
                                                                                                                                                                                                                                                                                                        else if pos('sechzig',str_hund)>0 then begin
                                                                                                                                                                                                                                                                                                                                               s:=copy(str_hund,pos('sech',str_hund)+4,pos('sechzig',str_hund)-(pos('sech',str_hund)+4));
                                                                                                                                                                                                                                                                                                                                               showmessage('После sech (3-е слово) может быть und'+#13+'добавьте und/исправьте: '+s);
                                                                                                                                                                                                                                                                                                                                               end
                                                                                                                                                                                                                                                                                                             else begin
                                                                                                                                                                                                                                                                                                                  s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)-length(simple[j]));
                                                                                                                                                                                                                                                                                                                  showmessage('После '+simple[j]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s)
                                                                                                                                                                                                                                                                                                                  end
                                                                                                                                                                                                                                                                                                        end
                                                                                                                                                                                                                                                                              else begin
                                                                                                                                                                                                                                                                                   s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund));
                                                                                                                                                                                                                                                                                   showmessage('После '+ simple[j]+' (3-е слово) ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                                                                   end
                                                                                                                                                                                                                                                                         end
                                                                                               else if pos(zig,str)=length(hard[i])+7+length(simple[j])+1 then if length(str)=length(hard[i])+7+length(simple[j])+3 then WToD(hard[i],true,'',simple[j]+'zig',false)
                                                                                                                                                               else begin s:=copy(str_hund,pos(zig,str_hund)+3,length(str_hund)); showmessage('После '+simple[j]+zig+' (3-е слово) ничего не должно быть'+#13+'удалите: '+s);end
                                                                                                    else if pos(zehn,str)=length(hard[i])+7+length(simple[j])+1 then if length(str)=length(hard[i])+7+length(simple[j])+4 then WToD(hard[i],true,simple[j],'',true)
                                                                                                                                                                     else begin s:=copy(str_hund,pos(zehn,str_hund)+4,length(str_hund)); showmessage('После '+simple[j]+zehn+' (3-е слово) ничего не должно быть'+#13+'удалите: '+s);end
                                                                                                         else if pos(und,str_hund)=length(simple[j])+1 then if length(str)=length(hard[i])+7+length(simple[j])+3 then showmessage('После und (4-е слово) должны быть десятки')
                                                                                                                                                            else begin
                                                                                                                                                                 for k:=1 to 8 do
                                                                                                                                                                 if pos(dec[k],str)=length(hard[i])+7+length(simple[j])+3+1 then if length(str)=length(hard[i])+7+length(simple[j])+3+7 then begin
                                                                                                                                                                                                                                                                                             WToD(hard[i],true,simple[j],dec[k],false);
                                                                                                                                                                                                                                                                                             break;
                                                                                                                                                                                                                                                                                             end
                                                                                                                                                                                                                                 else begin
                                                                                                                                                                                                                                      s:=copy(str_hund,pos(dec[k],str_hund)+length(dec[k]),length(str_hund));
                                                                                                                                                                                                                                      showmessage('После '+dec[k]+' (5-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                      break;
                                                                                                                                                                                                                                      end
                                                                                                                                                                 else if k=8 then begin
                                                                                                                                                                                  for z:=1 to 8 do
                                                                                                                                                                                  if pos(dec[z],str_hund)>pos(und,str_hund) then begin
                                                                                                                                                                                                                                 flag3:=false;
                                                                                                                                                                                                                                 s:=copy(str_hund,pos(und,str_hund)+3,pos(dec[z],str_hund)-(pos(und,str_hund)+3));
                                                                                                                                                                                                                                 showmessage('После und  (4-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                                                                                                 end;
                                                                                                                                                                                  if flag3 then begin s:=copy(str_hund,pos(und,str_hund)+3,length(str_hund)); showmessage('После und (4-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                                                                                                  end;
                                                                                                                                                                 end
                                                                                                              else begin
                                                                                                                   for zu:=1 to 8 do
                                                                                                                   if pos(dec[zu],str_hund)>length(simple[j]) then begin
                                                                                                                                                                   flag3:=false;
                                                                                                                                                                   if pos(und,str_hund)=0 then begin
                                                                                                                                                                                               s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),pos(dec[zu],str_hund)-(pos(simple[j],str_hund)+length(simple[j])));
                                                                                                                                                                                               showmessage('После '+simple[j]+' (3-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                                                                               end
                                                                                                                                                                   else if pos(und,str_hund)<pos(dec[zu],str_hund) then begin
                                                                                                                                                                                                                        s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),pos(und,str_hund)-(pos(simple[j],str_hund)+length(simple[j])));
                                                                                                                                                                                                                        showmessage('После '+simple[j]+' (3-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                                                                                                        end
                                                                                                                                                                        else begin
                                                                                                                                                                             s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),pos(dec[zu],str_hund)-(pos(simple[j],str_hund)+length(simple[j])));
                                                                                                                                                                             showmessage('После '+simple[j]+' (3-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                                                             end;
                                                                                                                                                                   end;
                                                                                                                   if flag3 then begin s:=copy(str_hund,pos(simple[j],str_hund)+length(simple[j]),length(str_hund)); showmessage('После '+simple[j]+' (3-е слово) бессмыслица'+#13+'исправьте/удалите: '+s)end;
                                                                                                                   end
                                                                            else begin
                                                                                 str_hund:=copy(str,length(hard[i])+7+1,length(str));
                                                                                 for g:=1 to 4 do if pos(hard[g],str_hund)= 1 then begin
                                                                                                                                   flag5:=true;
                                                                                                                                   break;
                                                                                                                                   end;
                                                                                 if flag5 then if length(str)=length(hard[i])+7+length(hard[g]) then showmessage('После '+hard[g]+' (3-е слово)'+#13+'не хватает: und+десятки/zehn/zig/hundert')
                                                                                               else if hard[g]='ein' then if pos(und,str_hund)=length(hard[g])+1 then if length(str)=length(hard[i])+7+length(hard[g])+3 then showmessage('После hundert (2-еслово) не должно быть только ein'+#13'добавьте: und + десятки')
                                                                                                                                                                      else begin
                                                                                                                                                                           for k:=1 to 8 do
                                                                                                                                                                           if pos(dec[k],str)=length(hard[g])+7+length(hard[g])+3+1 then if length(str)=length(hard[i])+7+length(hard[g])+3+7 then begin
                                                                                                                                                                                                                                                                                                   WToD(hard[i],true,hard[g],dec[k],false);
                                                                                                                                                                                                                                                                                                   break;
                                                                                                                                                                                                                                                                                                   end
                                                                                                                                                                                                                                         else begin
                                                                                                                                                                                                                                              s:=copy(str_hund,pos(dec[k],str_hund)+length(dec[k]),length(str_hund));
                                                                                                                                                                                                                                              showmessage('После '+dec[k]+' (5-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                              break;
                                                                                                                                                                                                                                              end
                                                                                                                                                                           else if k=8 then begin
                                                                                                                                                                                            for z:=1 to 8 do
                                                                                                                                                                                            if pos(dec[z],str_hund)>3+3 then begin
                                                                                                                                                                                                                             flag3:=false;
                                                                                                                                                                                                                             s:=copy(str_hund,pos(und,str_hund)+3,pos(dec[z],str_hund)-(pos(und,str_hund)+3));
                                                                                                                                                                                                                             showmessage('После und  (4-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                                                                                             end;
                                                                                                                                                                                            if flag3 then begin s:=copy(str_hund,pos(und,str_hund)+3,length(str_hund)); showmessage('После und (4-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                                                                                                            end
                                                                                                                                                                           end
                                                                                                                          else begin
                                                                                                                               flag3:=true;
                                                                                                                               for ku:=1 to 8 do
                                                                                                                               if pos(und,str_hund)=0 then if pos(dec[ku],str_hund)>3 then begin
                                                                                                                                                                                           flag3:=false;
                                                                                                                                                                                           s:=copy(str_hund,pos('ein',str_hund)+3,pos(dec[ku],str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                                           showmessage('После ein (3-е слово) '+'должно быть und'+#13+'добавьте/исправьте: '+s);
                                                                                                                                                                                           end
                                                                                                                                                            else
                                                                                                                               else if pos(dec[ku],str_hund)>3 then begin
                                                                                                                                                                    flag3:=false;
                                                                                                                                                                    s:=copy(str_hund,pos('ein',str_hund)+3,pos(und,str_hund)-(pos('ein',str_hund)+3));
                                                                                                                                                                    showmessage('После ein'+' (3-е слово) '+'должно быть und'+#13+'удалите: '+s);
                                                                                                                                                                    end;
                                                                                                                               if flag3 then begin s:=copy(str_hund,pos('ein',str_hund)+3,length(str_hund)); showmessage('После ein (3-е слово) бессмыслица'+#13+'исправьте/удалите: '+s)end;
                                                                                                                               end
                                                                                                    else if pos(zig,str)= length(hard[i])+7+length(hard[g])+1 then if length(str)=length(hard[i])+7+length(hard[g])+3 then WToD(hard[i],true,'',hard[g]+'zig',false)
                                                                                                                                                                   else begin
                                                                                                                                                                        s:=copy(str_hund,pos(zig,str_hund)+3,length(str_hund));
                                                                                                                                                                        showmessage('После '+hard[g]+zig+' (3-е слово) ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                        end
                                                                                                         else if pos(zehn,str)=length(hard[i])+7+length(hard[g])+1 then if length(str)=length(hard[i])+7+length(hard[g])+4 then if hard[g]<>'zwan' then WToD(hard[i],true,hard[g],'',true)
                                                                                                                                                                                                                                else showmessage('После zwan (3-е слово) нельзя zehn')
                                                                                                                                                                        else begin
                                                                                                                                                                             s:=copy(str_hund,pos(zehn,str_hund)+4,length(str_hund));
                                                                                                                                                                             showmessage('После '+hard[g]+zehn+' (3-е слово) ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                             end
                                                                                                              else if pos(und,str_hund)=length(hard[g])+1 then if length(str)=length(hard[i])+7+length(hard[g])+3 then showmessage('После '+und+' (4-е слово)'+#13+'не хватает: десятков')
                                                                                                                                                               else begin
                                                                                                                                                                    for k:=1 to 8 do
                                                                                                                                                                    if pos(dec[k],str)=length(hard[i])+7+length(hard[g])+3+1 then if length(str)=length(hard[i])+7+length(hard[g])+3+7 then begin
                                                                                                                                                                                                                                                                                            WToD(hard[i],true,hard[g],dec[k],false);
                                                                                                                                                                                                                                                                                            break;
                                                                                                                                                                                                                                                                                            end
                                                                                                                                                                                                                                  else begin
                                                                                                                                                                                                                                       s:=copy(str_hund,pos(dec[k],str_hund)+length(dec[k]),length(str_hund));
                                                                                                                                                                                                                                       showmessage('После '+dec[k]+' (5-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                                                                                                                       break;
                                                                                                                                                                                                                                       end
                                                                                                                                                                    else if k=8 then begin
                                                                                                                                                                                     for z:=1 to 8 do
                                                                                                                                                                                     if pos(dec[z],str_hund)>length(hard[g])+3 then begin
                                                                                                                                                                                                                                    flag3:=false;
                                                                                                                                                                                                                                    s:=copy(str_hund,pos(und,str_hund)+3,pos(dec[z],str_hund)-(pos(und,str_hund)+3));
                                                                                                                                                                                                                                    showmessage('После und  (4-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                                                                                                                    end;
                                                                                                                                                                                     if flag3 then begin s:=copy(str_hund,pos(und,str_hund)+3,length(str_hund)); showmessage('После und (4-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                                                                                                     end;
                                                                                                                                                                    end
                                                                                                                   else begin
                                                                                                                        for z:=1 to 8 do
                                                                                                                        if pos(und,str_hund)=0 then if pos(dec[z],str_hund)>3 then begin
                                                                                                                                                                                   flag3:=false;
                                                                                                                                                                                   s:=copy(str_hund,pos(hard[g],str_hund)+length(hard[g]),pos(dec[z],str_hund)-(pos(hard[g],str_hund)+length(hard[g])));
                                                                                                                                                                                   showmessage('После '+hard[g]+'(3-е слово) '+'должно быть und'+#13+'добавьте/исправьте: '+s);
                                                                                                                                                                                   end
                                                                                                                                                    else
                                                                                                                        else if pos(dec[z],str_hund)>3 then begin
                                                                                                                                                            flag3:=false;
                                                                                                                                                            s:=copy(str_hund,pos(hard[g],str_hund)+length(hard[g]),pos(und,str_hund)-(pos(hard[g],str_hund)+length(hard[g])));
                                                                                                                                                            showmessage('После '+hard[g]+'(3-е слово) '+'должно быть und'+#13+'удалите: '+s);
                                                                                                                                                            end;
                                                                                                                        if flag3 then begin s:=copy(str_hund,pos(hard[g],str_hund)+length(hard[g]),length(str_hund)); showmessage('После '+hard[g]+' (3-е слово) бессмыслица'+#13+'исправьте/удалите: '+s)end;
                                                                                                                        end
                                                                                 else begin
                                                                                      str_hund:=copy(str,pos('hundert',str)+7,length(str));
                                                                                      
                                                                                      for zs:=1 to 13 do
                                                                                      if pos(simple[zs],str_hund)<>0 then begin flags:=false; break;end;

                                                                                      for zh:=1 to 4 do
                                                                                      if pos(hard[zh],str)>pos('hundert',str)then begin flagh:=false;break;end;

                                                                                      if flags and flagh then showmessage('После hundert (2-е слово) ничего не должно быть'+#13+'удалите: '+str_hund);
                                                                                      if (not flags )and flagh  then begin
                                                                                                                     for zd:=1 to 8 do if pos(dec[zd],str_hund)>0 then begin flagd:=false;break; end;
                                                                                                                     if flagd then begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                     else if pos(dec[zd],str_hund)>pos(simple[zs],str_hund)then begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                          else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                                     end;

                                                                                      if flags and (not flagh)  then begin
                                                                                                                     for zd:=1 to 8 do if pos(dec[zd],str_hund)>0 then begin flagd:=false;break; end;
                                                                                                                     if flagd then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                     else if pos(dec[zd],str_hund)>pos(hard[zh],str_hund) then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                          else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                                     end;

                                                                                      if (not flags) and (not flagh) then begin
                                                                                                                          for zd:=1 to 8 do if pos(dec[zd],str_hund)>0 then begin flagd:=false;break; end;
                                                                                                                          if flagd then if pos(simple[zs],str_hund)>pos(hard[zh],str_hund)then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                                        else begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                          else if pos(simple[zs],str_hund)>pos(hard[zh],str_hund)then begin
                                                                                                                                                                                      if pos(dec[zd],str_hund)>pos(hard[zh],str_hund) then begin s:=copy(str_hund,1,pos(hard[zh],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+hard[zh]+#13+'удалите: '+s); end
                                                                                                                                                                                      else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                                                                                                      end
                                                                                                                               else begin
                                                                                                                                    if pos(dec[zd],str_hund)>pos(simple[zs],str_hund)then begin s:=copy(str_hund,1,pos(simple[zs],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+simple[zs]+#13+'удалите: '+s); end
                                                                                                                                    else begin s:=copy(str_hund,1,pos(dec[zd],str_hund)-1);showmessage('После hundert (2-е слово) может быть '+dec[zd]+#13+'удалите: '+s); end;
                                                                                                                                    end;
                                                                                                                          end;
                                                                                      end
                                                                                 end
                                                                            end
                   else if pos(zehn,str)=(length(hard[i])+1) then if (hard[i]='sech')or(hard[i]='sieb')then if length(str)=length(hard[i])+4 then WToD('',false,hard[i],'',true)    
                                                                                                            else begin s:=copy(str,pos(zehn,str)+4,length(str)); showmessage('После '+hard[i]+zehn+' (1-е слово) ничего не должно быть'+#13+'удалите: '+s);end
                                                                  else showmessage('После '+hard[i]+' (1-е слово) нельзя использовать ' +zehn)
                        else if pos(zig,str)=(length(hard[i])+1) then if (hard[i]='sech')or(hard[i]='sieb')or(hard[i]='zwan') then if length(str)=length(hard[i])+3 then WToD('',false,'',hard[i]+'zig',false)
                                                                                                                                   else begin s:=copy(str,pos(zig,str)+3,length(str)); showmessage('После '+hard[i]+zig+' (1-е слово) ничего не должно быть'+#13+'удалите: '+s);end
                                                                      else showmessage('После '+hard[i]+' (1-е слово) нельзя использовать ' +zig)
                             else if pos(und,str)=(length(hard[i])+1) then if length(str)=length(hard[i])+3 then showmessage('После und (2-е слово) должны быть десятки')
                                                                           else begin
                                                                                for l:=1 to 8 do
                                                                                if pos(dec[l],str)=(length(hard[i])+3+1) then if length(str)=length(hard[i])+3+7 then
                                                                                                                                                                 begin
                                                                                                                                                                 WToD('',false,hard[i],dec[l],false);
                                                                                                                                                                 break;
                                                                                                                                                                 end
                                                                                                                              else begin
                                                                                                                                   s:=copy(str,pos(dec[l],str)+length(dec[l]),length(str));
                                                                                                                                   showmessage('После '+dec[l]+' (3-е слово)'+#13+'больше ничего не должно быть'+#13+'удалите: '+s);
                                                                                                                                   break;
                                                                                                                                   end
                                                                                else if l=8 then begin
                                                                                                 for z:=1 to 8 do
                                                                                                 if pos(dec[z],str)>length(simple[i])+3 then begin
                                                                                                                                             flag3:=false;
                                                                                                                                             s:=copy(str,pos(und,str)+3,pos(dec[z],str)-(pos(und,str)+3));
                                                                                                                                             showmessage('После und  (2-е слово) должны быть десятки'+#13+'удалите: '+s);
                                                                                                                                             end;
                                                                                                 if flag3 then begin s:=copy(str,pos(und,str)+3,length(str)); showmessage('После und (2-е слово) должны быть десятки'+#13'исправьте: '+s) end;
                                                                                                 end;
                                                                                end
                                  else begin
                                       if length(str)>length(hard[i])then begin
                                                                          for zu:=1 to 8 do
                                                                          if pos(dec[zu],str)>length(hard[i]) then begin
                                                                                                                   flag3:=false;
                                                                                                                   if pos(und,str)=0 then begin
                                                                                                                                          s:=copy(str,pos(hard[i],str)+length(hard[i]),pos(dec[zu],str)-(pos(hard[i],str)+length(hard[i])));
                                                                                                                                          showmessage('После '+hard[i]+' (1-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                          end
                                                                                                                   else if pos(und,str)<pos(dec[zu],str) then begin
                                                                                                                                                              s:=copy(str,pos(hard[i],str)+length(hard[i]),pos(und,str)-(pos(hard[i],str)+length(hard[i])));
                                                                                                                                                              showmessage('После '+hard[i]+' (1-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                                                              end
                                                                                                                        else begin
                                                                                                                             s:=copy(str,pos(hard[i],str)+length(hard[i]),pos(dec[zu],str)-(pos(hard[i],str)+length(hard[i])));
                                                                                                                             showmessage('После '+hard[i]+' (1-е слово) должно быть und'+#13+'добавьте/исправьтве: '+s);
                                                                                                                             end;
                                                                                                                   end;
                                                                          if flag3 and(pos('hundert',str)=0) then begin
                                                                                                                  s:=copy(str,pos(hard[i],str)+length(hard[i]),length(str));
                                                                                                                  showmessage('После '+hard[i]+' (1-е слово) бессмыслица'+#13+'исправьте/удалите: '+s);
                                                                                                                  end
                                                                          else if pos('hundert',str)<>0 then begin
                                                                                                             s:=copy(str,pos(hard[i],str)+length(hard[i]),pos('hundert',str)-(pos(hard[i],str)+length(hard[i])));
                                                                                                             showmessage('После '+hard[i]+' (1-е слово) может быть hundert'+#13+'удалите: '+s);
                                                                                                             end;
                                                                          end
                                       end;
if not(flag1)and not(flag4) then begin
                                 if pos('hundert',str)>0 then showmessage('Добавьте единицы перед hundert')
                                 else showmessage('1-e слово не является числом');
                                 end;
end;



procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
if key=#13 then button1.Click;
end;

procedure TForm1.FormActivate(Sender: TObject);
begin
form1.Edit1.SetFocus;
end;

end.
