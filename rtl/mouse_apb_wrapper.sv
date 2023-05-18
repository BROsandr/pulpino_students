module mouse_apb_wrapper
#(
  parameter APB_ADDR_WIDTH = 12,  // APB slaves are 4KB by default
  parameter APB_DATA_WIDTH = 32
)
(
  input  logic                      clk_i,
  input  logic                      rstn_i,
  input  logic [APB_ADDR_WIDTH-1:0] apb_paddr_i,
  input  logic [APB_DATA_WIDTH-1:0] apb_pwdata_i,
  input  logic                      apb_pwrite_i,
  input  logic                      apb_psel_i,
  input  logic                      apb_penable_i,
  output logic [APB_DATA_WIDTH-1:0] apb_prdata_o,
  output logic                      apb_pready_o,
  output logic                      apb_pslverr_o,

  inout  logic                      ps2d_io,
  inout  logic                      ps2c_io
);

  // Local declarations

  localparam ADDR_X_POS     = 12'h0;
  localparam ADDR_Y_POS     = 12'h4;
  localparam ADDR_ACK       = 12'h8;
  localparam ADDR_BUTTON    = 12'hc;
  localparam ADDR_RST       = 12'h10;

  logic                      apb_write;
  logic                      apb_read;

  logic                      apb_sel_rst;
  logic                      apb_sel_ack;

  logic                      apb_sel_button;

  logic                      apb_sel_x_pos;
  logic                      apb_sel_y_pos;

  logic                      mouse_rstn;

  // From APB regs to mouse
  logic                      regs2mouse_ack;

  // From mouse to APB regs
  logic                      mouse2regs_button;
  logic                      mouse2regs_x_pos;
  logic                      mouse2regs_y_pos;

  logic                      ctrl_rst_ff;
  logic                      ctrl_rst_en;
  logic                      ctrl_rst_next;

  logic                      ctrl_ack_ff;
  logic                      ctrl_ack_en;
  logic                      ctrl_ack_next;

  logic [APB_DATA_WIDTH-1:0] x_pos_ff;
  logic [APB_DATA_WIDTH-1:0] x_pos_next;
  logic                      x_pos_en;

  logic [APB_DATA_WIDTH-1:0] y_pos_ff;
  logic [APB_DATA_WIDTH-1:0] y_pos_next;
  logic                      y_pos_en;

  logic [APB_DATA_WIDTH-1:0] button_ff;
  logic [APB_DATA_WIDTH-1:0] button_next;
  logic                      button_en;

  logic [APB_DATA_WIDTH-1:0] apb_dout_ff;
  logic [APB_DATA_WIDTH-1:0] apb_dout_next;
  logic                      apb_dout_en;

  logic                      apb_ready_ff;
  logic                      apb_ready_next;
  logic                      apb_ready_en;

  logic                      apb_err_ff;
  logic                      apb_err_next;
  logic                      apb_err_en;


  //////////////////////////
  // APB decoding         //
  //////////////////////////

  assign apb_write          = apb_psel_i & apb_pwrite_i;
  assign apb_read           = apb_psel_i & ~apb_pwrite_i;

  assign apb_sel_rst        = (apb_paddr_i == ADDR_RST);
  assign apb_sel_ack        = (apb_paddr_i == ADDR_ACK);

  assign apb_sel_button  = (apb_paddr_i == ADDR_BUTTON);

  assign apb_sel_x_pos  = (apb_paddr_i == ADDR_X_POS);
  assign apb_sel_y_pos  = (apb_paddr_i == ADDR_Y_POS);

  //////////////////////////
  // Control register     //
  //////////////////////////

  // RST bit

  assign ctrl_rst_en = (apb_write & apb_sel_rst);

  assign ctrl_rst_next = apb_pwdata_i[0];

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    ctrl_rst_ff <= '0;
  else if (ctrl_rst_en)
    ctrl_rst_ff <= ctrl_rst_next;

  // ACK bit

  assign ctrl_ack_en = (apb_write & apb_sel_ack)
                     | ctrl_ack_ff;

  assign ctrl_ack_next = (apb_write & apb_sel_ack) ? apb_pwdata_i[0]
                       :                             '0;

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    ctrl_ack_ff <= '0;
  else if (ctrl_ack_en)
    ctrl_ack_ff <= ctrl_ack_next;


  //////////////////////////
  // POS registers    //
  //////////////////////////

  // X pos

  assign x_pos_en = apb_write & apb_sel_x_pos;

  assign x_pos_next = apb_pwdata_i;

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    x_pos_ff <= '0;
  else if (x_pos_en)
    x_pos_ff <= x_pos_next;


  // Y pos

  assign y_pos_en = apb_write & apb_sel_y_pos;

  assign y_pos_next = apb_pwdata_i;

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    y_pos_ff <= '0;
  else if (y_pos_en)
    y_pos_ff <= y_pos_next;

  //////////////////////////
  // BUTTON register    //
  //////////////////////////

  assign button_en = apb_write & apb_sel_button;

  assign button_next = apb_pwdata_i;

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    button_ff <= '0;
  else if (button_en)
    button_ff <= button_next;

  //////////////////////////
  // APB data out         //
  //////////////////////////

  assign apb_dout_next = apb_sel_rst        ? APB_DATA_WIDTH'(ctrl_rst_ff)
                       : apb_sel_ack        ? APB_DATA_WIDTH'(ctrl_ack_ff)
                       : apb_sel_x_pos      ? APB_DATA_WIDTH'(mouse2regs_x_pos)
                       : apb_sel_y_pos      ? APB_DATA_WIDTH'(mouse2regs_y_pos)
                       : apb_sel_button     ? APB_DATA_WIDTH'(mouse2regs_button)
                       :                      '0;

  assign apb_dout_en = apb_read;

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    apb_dout_ff <= '0;
  else if (apb_dout_en)
    apb_dout_ff <= apb_dout_next;

  assign apb_prdata_o  = apb_dout_ff;


  //////////////////////////
  // APB ready            //
  //////////////////////////

  assign apb_ready_next = ( apb_psel_i & apb_penable_i ) & ~apb_ready_ff;

  assign apb_ready_en = (apb_psel_i & apb_penable_i)
                      | apb_ready_ff;

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    apb_ready_ff <= '0;
  else if (apb_ready_en)
    apb_ready_ff <= apb_ready_next;

  assign apb_pready_o  = apb_ready_ff;


  //////////////////////////
  // APB error            //
  //////////////////////////

  // Writes to status are forbidden
  // Writes to data_out registers are forbidden
  assign apb_err_next = ~apb_sel_rst
                      & ~apb_sel_ack
                      & ~(apb_sel_x_pos & ~apb_pwrite_i)
                      & ~(apb_sel_y_pos & ~apb_pwrite_i)
                      & ~(apb_sel_button & ~apb_pwrite_i);


  assign apb_err_en = (apb_psel_i & apb_penable_i);

  always_ff @(posedge clk_i or negedge rstn_i)
  if (~rstn_i)
    apb_err_ff <= '0;
  else if (apb_err_en)
    apb_err_ff <= apb_err_next;

  assign apb_pslverr_o = apb_err_ff;


  //////////////////////////
  // Mouse instantiation //
  //////////////////////////

  assign mouse_rstn = rstn_i && ctrl_rst_ff;

  assign regs2mouse_ack = ctrl_ack_ff;

  // Instantiation
  mouse_pos_wrapper mouse_pos_wrapper(
    .clk_i( clk_i ),
    .rstn_i( regs2mouse_ack ),
    .ack_i( regs2mouse_ack ),

    .ps2d_io( ps2d_io ),
    .ps2c_io( ps2c_io )
  );

endmodule
