module ADC_CTRL   (   
               iRST,
               iCLK,
               iCLK_n,
               iGO,
               
               
               oDIN,
               oCS_n,
               oSCLK,
               iDOUT,
               
               oADC_12_bit_channel_0,
               oADC_12_bit_channel_1,
               oADC_12_bit_channel_2,
               oADC_12_bit_channel_3,
               oADC_12_bit_channel_4,
               oADC_12_bit_channel_5,
               oADC_12_bit_channel_6,
               oADC_12_bit_channel_7
            );
               
input            iRST;
input            iCLK;
input            iCLK_n;
input          iGO;

output            oDIN;
output            oCS_n;
output            oSCLK;
input            iDOUT;

output  reg [11:0]    oADC_12_bit_channel_0;
output  reg [11:0]    oADC_12_bit_channel_1;
output  reg [11:0]    oADC_12_bit_channel_2;
output  reg [11:0]    oADC_12_bit_channel_3;
output  reg [11:0]    oADC_12_bit_channel_4;
output  reg [11:0]    oADC_12_bit_channel_5;
output  reg [11:0]    oADC_12_bit_channel_6;
output  reg [11:0]    oADC_12_bit_channel_7;

reg     [2:0]    channel;
reg               data;
reg               go_en;
reg               sclk;
reg      [3:0]      cont;
reg      [3:0]      m_cont;
reg      [11:0]   adc_data;
reg      [31:0]   adc_counter;

assign   oCS_n      =   ~go_en;
assign   oSCLK      =   (go_en)? iCLK:1;
assign   oDIN      =   data;

always@( iCLK )//posedge iGO or posedge iRST)
begin
   if(iRST)
      go_en   <=   0;
   else
   begin
      if(iGO)
         go_en   <=   1;
   end
end

always@(posedge iCLK or negedge go_en)
begin
   if(!go_en)
      cont   <=   0;
   else
   begin
      if(iCLK)
         cont   <=   cont + 1;
   end
end

always@(posedge iCLK_n)
begin
   if(iCLK_n)
      m_cont   <=   cont;
end

always@(posedge iCLK_n or negedge go_en)
begin
   if(!go_en)
      data   <=   0;
   else
   begin
      if(iCLK_n)
      begin
         if (cont == 2)
            data   <=   channel[2];
         else if (cont == 3)
            data   <=   channel[1];
         else if (cont == 4)
            data   <=   channel[0];
         else
            data   <=   0;
      end
   end
end

always@(posedge iCLK or negedge go_en)
begin
   if(!go_en)
   begin
      adc_data   <=   0;
   end
   else
   if(iCLK)
      begin
         if (m_cont == 4)
            adc_data[11]   <=   iDOUT;
         else if (m_cont == 5)
            adc_data[10]   <=   iDOUT;
         else if (m_cont == 6)
            adc_data[9]      <=   iDOUT;
         else if (m_cont == 7)
            adc_data[8]      <=   iDOUT;
         else if (m_cont == 8)
            adc_data[7]      <=   iDOUT;
         else if (m_cont == 9)
            adc_data[6]      <=   iDOUT;
         else if (m_cont == 10)
            adc_data[5]      <=   iDOUT;
         else if (m_cont == 11)
            adc_data[4]      <=   iDOUT;
         else if (m_cont == 12)
            adc_data[3]      <=   iDOUT;
         else if (m_cont == 13)
            adc_data[2]      <=   iDOUT;
         else if (m_cont == 14)
            adc_data[1]      <=   iDOUT;
         else if (m_cont == 15)
            adc_data[0]      <=   iDOUT;
         else if (m_cont == 1)
            begin                  
               if ( adc_counter < 32'd20 )
               begin
                  adc_counter <= adc_counter + 1'b1;
               end
               else
               begin         
                  if (channel == 3'd0)
                     oADC_12_bit_channel_0 <= adc_data;
                  else if (channel == 3'd1)
                     oADC_12_bit_channel_1 <= adc_data;
                  else if (channel == 3'd2)
                     oADC_12_bit_channel_2 <= adc_data;
                  else if (channel == 3'd3)
                     oADC_12_bit_channel_3 <= adc_data;
                  else if (channel == 3'd4)
                     oADC_12_bit_channel_4 <= adc_data;
                  else if (channel == 3'd5)
                     oADC_12_bit_channel_5 <= adc_data;
                  else if (channel == 3'd6)
                     oADC_12_bit_channel_6 <= adc_data;
                  else if (channel == 3'd7)
                     oADC_12_bit_channel_7 <= adc_data;
               
                  adc_counter <= 32'd0;
                  channel <= channel + 1'b1;
               end
            end
      end
end

endmodule
