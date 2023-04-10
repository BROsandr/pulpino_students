module kuznechik_cipher(
    input  logic         clk_i,     // Тактовый сигнал
    input  logic         resetn_i,  // Синхронный сигнал сброса с активным уровнем LOW
    input  logic         request_i, // Сигнал запроса на начало шифрования
    input  logic         ack_i,     // Сигнал подтверждения приема зашифрованных данных
    input  logic [127:0] data_i,    // Шифруемые данные

    output logic         busy_o,    // Сигнал, сообщающий о невозможности приёма
                                    // очередного запроса на шифрование, поскольку
                                    // модуль в процессе шифрования предыдущего
                                    // запроса
    output logic         valid_o,   // Сигнал готовности зашифрованных данных
    output logic [127:0] data_o     // Зашифрованные данные
);

  enum { 
    IDLE_S,
    KEY_PHASE_S,
    S_PHASE_S,
    L_PHASE_S,
    FINISH_S
  } state_ff, state_next;
  
  logic [7:0]   data_galua_in [15:0];
  
  logic [3:0]   l_phase_counter_ff;
  logic [3:0]   l_phase_counter_next;

  logic [7:0]   data_key_result_bytes      [15:0];
  logic [7:0]   data_nonlinear_result_ff   [15:0];
  logic [7:0]   data_nonlinear_result_next [15:0];

  logic [127:0] data_key_result_ff;
  logic [127:0] round_key;

  logic [127:0] data_ff;

  reg   [7:0]   S_box_mem     [0:255];
  reg   [7:0]   L_mul_16_mem  [0:255];
  reg   [7:0]   L_mul_32_mem  [0:255];
  reg   [7:0]   L_mul_133_mem [0:255];
  reg   [7:0]   L_mul_148_mem [0:255];
  reg   [7:0]   L_mul_192_mem [0:255];
  reg   [7:0]   L_mul_194_mem [0:255];
  reg   [7:0]   L_mul_251_mem [0:255];

  reg   [127:0] key_mem [0:9];

  logic [3:0]   trial_num_ff;
  logic [3:0]   trial_num_next;
  logic [127:0] trial_input_mux;
  logic [127:0] trial_output;

  logic         valid_ff;

  logic         request_ff;

  logic         resetn_buff_ff;
  logic         resetn_ff;

  logic         busy_ff;
  logic         busy_next;

  logic         ack_ff;

  logic [7:0]   galua_summ;
  
  logic [7:0]   data_galua_shreg_ff   [15:0];
  logic [7:0]   data_galua_shreg_next [15:0];
  logic [7:0]   data_galua_result     [15:0];

  logic         state_en;

  initial begin
    $readmemh("keys.mem"  , key_mem );
    $readmemh("S_box.mem" , S_box_mem );

    $readmemh("L_16.mem" , L_mul_16_mem );
    $readmemh("L_32.mem" , L_mul_32_mem );
    $readmemh("L_133.mem", L_mul_133_mem);
    $readmemh("L_148.mem", L_mul_148_mem);
    $readmemh("L_192.mem", L_mul_192_mem);
    $readmemh("L_194.mem", L_mul_194_mem);
    $readmemh("L_251.mem", L_mul_251_mem);
  end

  assign trial_input_mux = (trial_num_ff == 0) ? data_ff
                         :                       trial_output ;

  // Key overlay
  assign round_key = key_mem[trial_num_ff];

  always_ff @(posedge clk_i)
    if (~resetn_ff)
      request_ff <= '0;
    else
      request_ff <= request_i;

  always_ff @(posedge clk_i)
    if (~resetn_ff)
      ack_ff <= '0;
    else
      ack_ff <= ack_i;

  always_ff @(posedge clk_i)
    resetn_buff_ff <= resetn_i;

  always_ff @(posedge clk_i)
    resetn_ff <= resetn_buff_ff;

  always_ff @(posedge clk_i)
    if (~resetn_ff)
      data_ff <= '0;
    else
      data_ff <= data_i;

  always_ff @(posedge clk_i)
    if (~resetn_ff)
      data_key_result_ff <= '0;
    else if (state_ff == KEY_PHASE_S)
      data_key_result_ff <= trial_input_mux ^ round_key;

  // Linear overlay

  for (genvar i = 0; i < 16; i++) begin
    always_ff @(posedge clk_i) begin
      if (~resetn_ff)
        data_nonlinear_result_ff[i] <= '0;
      else if (state_ff == S_PHASE_S)
        data_nonlinear_result_ff[i] <= data_nonlinear_result_next[i];
    end

    assign data_nonlinear_result_next[i] = S_box_mem[data_key_result_bytes[i]];
  end

  generate;
    for (genvar i=0; i<16; i++) begin
      assign data_key_result_bytes   [i] = data_key_result_ff[((i+1)*8)-1:(i*8)];
    end
  endgenerate

  // Galua overlay

  assign data_galua_in = ( ~|l_phase_counter_ff ) ? ( data_nonlinear_result_ff ) : ( data_galua_shreg_ff );

  // Table Ratio  148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148, 1
  // Number Index  15, 14,  13, 12,  11,  10, 9,   8, 7,   6,   5,  4,   3,  2,   1, 0
  assign data_galua_result[15]  = L_mul_148_mem [data_galua_in[15]];
  assign data_galua_result[14]  = L_mul_32_mem  [data_galua_in[14]]; 
  assign data_galua_result[13]  = L_mul_133_mem [data_galua_in[13]]; 
  assign data_galua_result[12]  = L_mul_16_mem  [data_galua_in[12]]; 
  assign data_galua_result[11]  = L_mul_194_mem [data_galua_in[11]]; 
  assign data_galua_result[10]  = L_mul_192_mem [data_galua_in[10]]; 
  assign data_galua_result[9]   =                data_galua_in[9] ;
  assign data_galua_result[8]   = L_mul_251_mem [data_galua_in[8]]; 
  assign data_galua_result[7]   =                data_galua_in[7] ;
  assign data_galua_result[6]   = L_mul_192_mem [data_galua_in[6]]; 
  assign data_galua_result[5]   = L_mul_194_mem [data_galua_in[5]]; 
  assign data_galua_result[4]   = L_mul_16_mem  [data_galua_in[4]]; 
  assign data_galua_result[3]   = L_mul_133_mem [data_galua_in[3]]; 
  assign data_galua_result[2]   = L_mul_32_mem  [data_galua_in[2]]; 
  assign data_galua_result[1]   = L_mul_148_mem [data_galua_in[1]]; 
  assign data_galua_result[0]   =                data_galua_in[0] ;


  generate;

    always_comb begin
      galua_summ = '0;
      for (int i = 0; i < 16; i++)
        galua_summ = galua_summ ^ data_galua_result[i];
    end


    always_comb begin
      data_galua_shreg_next[15] = galua_summ;
      for (int i = 14; i >= 0; i--)
        data_galua_shreg_next[i] = ( ~|l_phase_counter_ff ) ? ( data_nonlinear_result_ff[i+1] ) : ( data_galua_shreg_ff[i+1] );
    end


    for (genvar i = 0; i < 16; i++) begin
      always_ff @(posedge clk_i) begin
        if (~resetn_ff)
          data_galua_shreg_ff[i] <= '0;
        else if (state_ff == L_PHASE_S)
          data_galua_shreg_ff[i] <= data_galua_shreg_next[i];
      end
    end

    for (genvar i = 0; i < 16; i++)
      assign trial_output[((i+1)*8)-1:(i*8)] = data_galua_shreg_ff[i];

  endgenerate

  always_ff @( posedge clk_i )
    if( ~resetn_ff )
      trial_num_ff <= '0;
    else if ( state_ff == IDLE_S )
      trial_num_ff <= '0;
    else if( state_ff == KEY_PHASE_S )
      trial_num_ff <= trial_num_next;

  assign trial_num_next = trial_num_ff + 1;

  always_ff @( posedge clk_i )
    if( ~resetn_ff )
      state_ff <= IDLE_S;
    else if( state_en )
      state_ff <= state_next;

  assign state_en = request_ff || state_ff == KEY_PHASE_S || state_ff==  S_PHASE_S || &l_phase_counter_ff || ack_ff;

  always_ff @( posedge clk_i )
    if( ~resetn_ff )
      l_phase_counter_ff <= '0;
    else if( state_ff == IDLE_S )
      l_phase_counter_ff <= '0;
    else if( state_ff == L_PHASE_S )
      l_phase_counter_ff <= l_phase_counter_next;

  assign l_phase_counter_next = l_phase_counter_ff + 1;

  always_comb
    begin
      state_next = state_ff;
      case( state_ff)
        IDLE_S: begin
          if( request_ff )
            state_next = KEY_PHASE_S;
        end

        KEY_PHASE_S: begin
          if( trial_num_ff == 4'd9 )
            state_next = FINISH_S;
          else
            state_next = S_PHASE_S;
        end

        S_PHASE_S: begin
          state_next = L_PHASE_S;
        end

        L_PHASE_S: begin
          if( &l_phase_counter_ff )
            state_next = KEY_PHASE_S;
        end

        FINISH_S: begin
          if( ack_ff )
            state_next = IDLE_S;
        end

        default: begin
          state_next = IDLE_S;
        end
      endcase
    end

  assign data_o = data_key_result_ff;

  always_ff @( posedge clk_i )
    if( ~resetn_ff )
      busy_ff <= '0;
    else
      busy_ff <= busy_next;

  assign busy_next = state_ff != IDLE_S;

  assign busy_o = busy_ff;

  always_ff @( posedge clk_i )
    if( ~resetn_ff )
      valid_ff <= '0;
    else if( state_ff == FINISH_S )
      valid_ff <= 1'b1;
    else if( state_ff == IDLE_S )
      valid_ff <= 1'b0;

  assign valid_o = valid_ff;
endmodule
