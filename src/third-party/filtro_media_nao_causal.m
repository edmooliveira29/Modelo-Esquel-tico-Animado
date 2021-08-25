%
%
%
%
% [sinal_filtrado, media] = filtro_media_nao_causal(sinal,janela);
%
% Sintaxe: janela -> � o tamanho da janela de dados que ser� ultilizado no
%                    c�lculo da m�dia
%

% load galera_1_ECG.txt;

function [sinal_filtrado, media] = filtro_media_nao_causal(sinal,janela);

% close all
% clear;
% clear;
% load ECG.txt;

% load sinal_medio.txt;
% load sinal_com_media_adicionada.txt

% ECG = galera_1_ECG(1:10000,2)';

% sinal = ECG;
% sinal = sinal_com_media_adicionada;
% sinal = sinal_filtrado;

% janela = 17; %sempre usar um n�mero �mpar %janela = 11 para ECG e 17 para sinal_com_media_adicionada  (default)

M = fix(janela/2);
sinal_modificado = [zeros(1,fix(janela/2)) sinal zeros(1,fix(janela/2))];

% M = round(janela/2);
% sinal_modificado = [zeros(1,round(janela/2)) sinal zeros(1,round(janela/2))];


for n = 1+M:length(sinal)+M
    
    media(n-M) = mean(sinal_modificado(n-M:n+M));
    
end;

% figure
% plot(media,'r-')
% hold on
% plot(sinal,'k-')


sinal_filtrado = sinal - media; %subtra�da a m�dia

% figure
% plot(sinal_filtrado)
