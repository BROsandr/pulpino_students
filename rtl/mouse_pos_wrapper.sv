module mouse_pos_wrapper #(
  parameter WIDTH,
  parameter HEIGHT,
  parameter X_POS_WIDTH,
  parameter Y_POS_WIDTH
) (
  input logic clk_i,
  input logic rstn_i,
  input logic ack_i,
  
  output logic [X_POS_WIDTH:0] x_pos_o,
  output logic [Y_POS_WIDTH:0] y_pos_o,
  output logic [2:0]           btnm_o,

  inout wire  ps2d_io,
  inout wire  ps2c_io
);

  logic [X_POS_WIDTH:0] x_pos_ff;
  logic [Y_POS_WIDTH:0] y_pos_ff;
  logic [X_POS_WIDTH:0] x_pos_next;
  logic [Y_POS_WIDTH:0] y_pos_next;

  logic [8:0] xm;
  logic [8:0] ym;

  logic [2:0] btnm_ff;
  logic [2:0] btnm;
  logic [2:0] btnm_next;

  logic       m_done_tick;
  
  logic       rst;
  assign      rst = ~rstn_i;

  mouse mouse(  
    .clk( clk_i ), 
    .reset( rst ),  
    .ps2d( ps2d_io ), 
    .ps2c( ps2c_io ),  
    .xm( xm ), 
    .ym( ym ),  
    .btnm( btnm ),  
    .m_done_tick( m_done_tick )  
  ); 

  always_ff @( posedge clk_i or negedge rstn_i )
    if( ~rstn_i ) begin
      x_pos_ff <= '0;
      y_pos_ff <= '0;
    end else if( m_done_tick ) begin
      x_pos_ff <= x_pos_next;
      y_pos_ff <= y_pos_next;
    end 

  assign y_pos_next = y_pos_ff + { { (X_POS_WIDTH-9){xm[8]} }, xm };
  assign x_pos_next = x_pos_ff - { { (Y_POS_WIDTH-9){ym[8]} }, ym };

  always_ff @( posedge clk_i or negedge rstn_i )
    if( ~rstn_i )  btnm_ff <= '0;
    else           btnm_ff <= btnm_next;
    
  assign btnm_next = ack_i ? '0 : btnm_ff | btnm;

  assign btnm_o  = btnm_ff;
  assign x_pos_o = x_pos_ff;
  assign y_pos_o = y_pos_ff;

endmodule
