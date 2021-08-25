%
%
%
%
% [sinal_filtrado, media] = filtro_media_nao_causal(sinal,janela);
%
% Sintaxe: janela -> é o tamanho da janela de dados que será ultilizado no
%                    cálculo da média
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

% janela = 17; %sempre usar um número ímpar %janela = 11 para ECG e 17 para sinal_com_media_adicionada  (default)

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


sinal_filtrado = sinal - media; %subtraída a média

% figure
% plot(sinal_filtrado)
